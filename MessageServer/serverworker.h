#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QReadWriteLock>
#include <QFile>
class QJsonObject;
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString getUserID() const;
    void setUserID(const QString &userID);
    void sendJson(const QJsonObject &jsonData);
signals:
    void disconnectedFromClient();
    void jsonReceived(const QJsonObject &jsonDoc);
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    QTcpSocket *m_serverSocket;
    QString m_userID;
    mutable QReadWriteLock m_userNameLock;
    quint32 m_blockSize;
    void receiveFile(QDataStream &in);
};

#endif // SERVERWORKER_H
