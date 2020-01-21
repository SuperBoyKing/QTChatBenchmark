#include "serverworker.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDataStream>
#include <QFile>

ServerWorker::ServerWorker(QObject *parent)
    : QObject(parent)
{
    m_blockSize=0;
    m_serverSocket = new QTcpSocket(this);
    // Connect readyRead() to the slot that will take care of reading the data in
    connect(m_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::receiveJson);
    // Forward the disconnected and error signals coming from the socket
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    //connect(m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ServerWorker::error);
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    // Now crate a temporary QJsonDocument from the object and then convert it
    // To its UTF-8 encoded version and use QJsonDocument::Compact to save bandwidth
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Indented);
    // Notify the central server we are about to send the message
    emit logMessage("Sending to " + getUserID() + " - " + QString::fromUtf8(jsonData));
    // Send the message to the socket in the exact same way did in the client
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    socketStream << jsonData;
}

void ServerWorker::disconnectFromClient()
{
    m_serverSocket->disconnectFromHost();
}

QString ServerWorker::getUserID() const
{
    m_userNameLock.lockForRead();
    const QString result = m_userID;
    m_userNameLock.unlock();
    return result;
}

void ServerWorker::setUserID(const QString &userID)
{
    m_userNameLock.lockForWrite();
    m_userID = userID;
    m_userNameLock.unlock();
}

void ServerWorker::receiveFile(QDataStream &in)
{
    if (m_blockSize == 0) {
        if (m_serverSocket->bytesAvailable() < sizeof(quint32))
            return;
        in >> m_blockSize;
    }

    if (m_serverSocket->bytesAvailable() < m_blockSize)
        return;

    QString fileName;
    // Get sending file name
    in >> fileName;
    QByteArray line = m_serverSocket->readAll();

    QString filePath = "C:/Users/SuperBoyKing/Documents/Qt/QtProject/MessageServer/ServerFile"; // Server file path for receiving
    fileName = fileName.section("/", -1);
    QFile target(filePath + "/" + fileName);

    if (!target.open(QIODevice::WriteOnly)) {
        qDebug() << "Can't open file for written";
        return;
    }
    target.write(line);

    target.close();

    fileName = nullptr;
    line = nullptr;
    m_blockSize = 0;

    emit logMessage("downloaded File....");
}

void ServerWorker::receiveJson()
{
    // Prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    // Create a QDataStream operating on the socket
    QDataStream socketStream(m_serverSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_12);

    // Start an infinite loop
    for (;;) {
       // Start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // Try to read the JSON data
        QByteArray data;
        socketStream >> data;
        // Loop and try to read more JSONs if they are avaliable
            // Successfully read some data
            // Now need to make sure it's in fact a valied JSON
            QJsonParseError parseError;
            // Try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
            if (parseError.error == QJsonParseError::NoError || jsonDoc.isObject()) {
                emit jsonReceived(jsonDoc.object());
                socketStream.commitTransaction();
            } else {
                socketStream.rollbackTransaction();
                break;
            }
            // The read falied, the socket goes automatically back to the state it was in before the transaction started
            // And just exit the loop
    }
    receiveFile(socketStream);
}
