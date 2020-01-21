#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
class QStandardItemModel;
namespace Ui {
class ServerWindow;
}
class CentralServer;
class ServerWorker;
class ServerWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWindow)
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
    CentralServer *m_centralServer;
    QStandardItemModel * m_userModel;
    ServerWorker *m_serverWorker;
private slots:
    void logMessage(const QString &msg);
    void on_pushButton_startServer_clicked();
    void userJoin(const QString &userName);
    void userLeft(const QString &userName);
    void sendMessage();
};

#endif // SERVERWINDOW_H
