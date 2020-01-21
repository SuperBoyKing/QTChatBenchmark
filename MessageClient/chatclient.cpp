#include "chatclient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overload, see the Qtdocs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    // Reset the m_loggedIn variable when user disconnect. Since the operation is trivial use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void ChatClient::login(const QString &userID)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) {
        // Create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);
        // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_12);
        // Create the JSON to send server
        QJsonObject message;
        message["type"] = QStringLiteral("login");
        message["userID"] = userID;
        // Send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

void ChatClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return;
    // Create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_8);
    // Create the JSON to send server
    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    // Send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ChatClient::sendFile(const QString &fileName)
{
    m_file = new QFile(fileName);

    if (m_clientSocket->state() != QAbstractSocket::ConnectedState || !m_file->open(QIODevice::ReadOnly)) {
        qDebug() << "Socket connectless or File is not open.";
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    // Out stream current fileName
    out << quint32(0) << m_file->fileName();

    // Write file into byteArray
    QByteArray data = m_file->readAll();
    block.append(data);
    m_file->close();

    // Set device pointer to zero
    out.device()->seek(0);
    out << (quint32)(block.size() - sizeof(quint32));
    qint64 x = 0;

    while (x < block.size()) {
        qint64 y = m_clientSocket->write(block);
        x += y;
        qDebug() << x;
    }
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::JsonReceived(const QJsonObject &doc)
{
    // Actions depend on the type of message
    const QJsonValue typeVal = doc.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;

    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) {
        if(m_loggedIn)
            return;
        // If succes filed will contain the result of our attempt to login
        const QJsonValue resultVal = doc.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return;

        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            emit loggedIn();
            return;
        }

        // If login attempt failed, we extract the reason of the failure fonr the JSON
        // and notify it via the logibError signal
        const QJsonValue reasonVal = doc.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());

    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) {
        // Extract the text field containing the chat text
        const QJsonValue textVal = doc.value(QLatin1String("text"));
        // Extract the sender field containing the username of the sender
        const QJsonValue senderVal = doc.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return;
        if (senderVal.isNull() || !senderVal.isString())
            return;

        // The notify a new message was received via the messageReceived signal
        emit messageReceived(senderVal.toString(), textVal.toString());

    } else if (typeVal.toString().compare(QLatin1String("newUser"), Qt::CaseInsensitive) == 0) {
        // Extract the username of the new user
        const QJsonValue userIDVal = doc.value(QLatin1String("userID"));
        if (userIDVal.isNull() || !userIDVal.isString())
            return;

        // The notify of the new user via the userJoined signal
        emit userJoined(userIDVal.toString());

    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) {
        // Extract the username of the new user
        const QJsonValue userIDVal = doc.value(QLatin1String("userID"));
        if (userIDVal.isNull() || !userIDVal.isString())
            return;
        // The notify of the user disconnected the userLeft signal
        emit userLeft(userIDVal.toString());
    }
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::onReadyRead()
{
    // Prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // Create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_12);
    for (;;) {
        // Start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // Try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError || jsonDoc.isObject())
                JsonReceived(jsonDoc.object());
        } else {
            break;
        }
    }
}
