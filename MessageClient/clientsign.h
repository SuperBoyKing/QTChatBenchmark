#ifndef CLIENTSIGN_H
#define CLIENTSIGN_H

#include "chatclient.h"
#include "clientsignup.h"
#include "messengerwindow.h"
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

class ChatClient;
namespace Ui {
class ClientSign;
}

class ClientSign : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(ClientSign)
public:
    explicit ClientSign(QWidget *parent = nullptr);
    ~ClientSign();
private slots:
    void on_pushButton_signup_clicked();
    void attemptLogin();
signals:

private:
    Ui::ClientSign *ui;
    ChatClient *m_chatClient;
    ClientSignUp *clientSingUp;
    MessengerWindow *messenger;
    bool user_search(const QString &userID, const QString &password);
};

#endif // CLIENTSIGN_H
