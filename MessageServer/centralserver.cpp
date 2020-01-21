#include "centralserver.h"
#include "serverworker.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>

CentralServer::CentralServer(QObject *parent)
    : QTcpServer(parent)
    , m_idealThreadCount(qMax(QThread::idealThreadCount(), 1))
{
    m_availableThreads.reserve(m_idealThreadCount);
    m_threadsLoad.reserve(m_idealThreadCount);
}

CentralServer::~CentralServer()
{
    for (QThread *singleThread : m_availableThreads) {
        singleThread->quit();
        singleThread->wait();
    }
}

void CentralServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }
    int threadIdx = m_availableThreads.size();
    if(threadIdx < m_idealThreadCount) {        // Add a new thread
        m_availableThreads.append(new QThread(this));
        m_threadsLoad.append(1);
        m_availableThreads.last()->start();
    } else {
        // Find the thread with the least amount of clients and use it
        threadIdx = std::distance(m_threadsLoad.cbegin(), std::min_element(m_threadsLoad.cbegin(), m_threadsLoad.cend()));
        ++m_threadsLoad[threadIdx];
    }
    worker->moveToThread(m_availableThreads.at(threadIdx));
    connect(worker, &ServerWorker::logMessage, this, &CentralServer::logMessage);
    connect(m_availableThreads.at(threadIdx), &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&CentralServer::userDiconnected, this, worker, threadIdx));
    connect(worker, &ServerWorker::error, this, std::bind(&CentralServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&CentralServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(this, &CentralServer::stopAllClients, worker, &ServerWorker::disconnectFromClient);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Conneceted"));
}

void CentralServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    QTimer::singleShot(0, destination, std::bind(&ServerWorker::sendJson, destination, message));
}

void CentralServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void CentralServer::serverSendMessage(const QString &message)
{
    QJsonObject serverMessage;
    serverMessage["type"] = QStringLiteral("message");
    serverMessage["text"] = message;
    serverMessage["sender"] = QStringLiteral("Server");
    broadcast(serverMessage, nullptr);
}

void CentralServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage("JSON received " + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->getUserID().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void CentralServer::userDiconnected(ServerWorker *sender, int threadIdx)
{
    emit userLeft(sender->getUserID());
    --m_threadsLoad[threadIdx];
    m_clients.removeAll(sender);
    const QString userID = sender->getUserID();
    if (!userID.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = QStringLiteral("userdisconnected");
        disconnectedMessage["userID"] = userID;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userID + " disconnecetd");
    }
    sender->deleteLater();
}

void CentralServer::userError(ServerWorker* sender)
{
    Q_UNUSED(sender)
    emit logMessage("Error from " + sender->getUserID());
}

void CentralServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void CentralServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = doc.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;

    const QJsonValue userIDVal = doc.value(QLatin1String("userID"));
    if (userIDVal.isNull() || !userIDVal.isString())
        return;

    const QString newUserID = userIDVal.toString().simplified();
    if (newUserID.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->getUserID().compare(newUserID, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message["type"] = QStringLiteral("login");
            message["success"] = false;
            message["reason"] = QStringLiteral("duplicate userName");
            sendJson(sender, message);
            return;
        }
    }


    sender->setUserID(newUserID);
    // add userName at the serverwindow userList
    emit userJoin(sender->getUserID());
    QJsonObject successMessage;
    successMessage["type"] = QLatin1String("login");
    successMessage["success"] = true;
    sendJson(sender, successMessage);
    QJsonObject connectedMessage;
    connectedMessage["type"] = QLatin1String("newuser");
    connectedMessage["userID"] = newUserID;
    broadcast(connectedMessage, sender);
}

void CentralServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = doc.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) != 0)
        return;

    const QJsonValue textVal = doc.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    message["sender"] = sender->getUserID();
    broadcast(message, sender);
}
