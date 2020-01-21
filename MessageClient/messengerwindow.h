#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
class ChatClient;
class ClientSign;
class QStandardItemModel;
namespace Ui {
class MessengerWindow;
}

class MessengerWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MessengerWindow)
public:
    explicit MessengerWindow(QString userName, QWidget *parent = nullptr);
    ~MessengerWindow();

private:
    Ui::MessengerWindow *ui;
    ChatClient *m_chatClient;
    ClientSign *m_clientSign;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;
    QString m_userID;
private slots:
    void connectedToServer();
    void attemptConnection();
    void MessageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void sendFile();
    void userJoined(const QString &userName);
    void userLeft(const QString &userName);
    void error(QAbstractSocket::SocketError socketError);
    void disconnectedFromServer();
    void loginFailed(const QString &reason);
};

#endif // MESSENGERWINDOW_H
