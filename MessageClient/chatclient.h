#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
class QHostAddress;
class QJsonDocument;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void sendFile(const QString &fileName);
    void disconnectFromHost();
public slots:
    void onReadyRead();
signals:
    void connected();
    void disconnected();
    void loggedIn();
    void loginError(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &userID);
    void userLeft(const QString &userID);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    QFile *m_file;
    void JsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
