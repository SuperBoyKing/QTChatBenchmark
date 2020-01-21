#ifndef CENTRALSERVER_H
#define CENTRALSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QVector>
class QThread;
class ServerWorker;
class QJsonObject;
class CentralServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(CentralServer)
public:
    explicit CentralServer(QObject *parent = nullptr);
    void serverSendMessage(const QString &message);
    ~CentralServer() override;
protected:
    void incomingConnection(qintptr socketDescriptor) override;
    void receivFile(QDataStream &in);
signals:
    void logMessage(const QString &msg);
    void stopAllClients();
    void userJoin(const QString &userName);
    void userLeft(const QString &userName);
public slots:
    void stopServer();
private slots:
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDiconnected(ServerWorker *sender, int threadIdx);
    void userError(ServerWorker *sender);
private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    const int m_idealThreadCount;
    QVector<QThread *> m_availableThreads;
    QVector<int> m_threadsLoad;
    QVector<ServerWorker*> m_clients;
    QVector<const QString*> m_userList;
};

#endif // CENTRALSERVER_H
