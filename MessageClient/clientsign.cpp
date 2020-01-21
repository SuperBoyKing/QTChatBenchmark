#include "clientsign.h"
#include "ui_clientsign.h"
#include "clientsignup.h"
#include "chatclient.h"
#include <QMessageBox>
#include <QDebug>

ClientSign::ClientSign(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::ClientSign)
  , m_chatClient(new ChatClient(this))
{
    this->setFixedSize(585, 410);
    ui->setupUi(this);
    connect(ui->pushButton_signin, &QPushButton::clicked, this, &ClientSign::attemptLogin);
}

ClientSign::~ClientSign()
{
    delete ui;
}

// If user pressed SignIn button!
void ClientSign::attemptLogin()
{
    QString userID = ui->lineEdit_userId->text();
    QString password = ui->lineEdit_password->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/db/Client.db");
    if (!db.open()) {
      QMessageBox::critical(this, "Error", "Database not connected!");
      return;
    } else if (userID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please note your ID");
    } else if (password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please note your password");
    } else {
        // This statement is perfrom password encryption using hash algorithm.
        QByteArray encryption = QCryptographicHash::hash(password.toLocal8Bit(),
                                QCryptographicHash::Keccak_256).toBase64();
        QString e_password = QString::fromUtf8(encryption);

        if(user_search(userID, e_password)) {
            QSqlQuery qry("select * from ClientInfo where userID = '"+userID+"' and password='"+e_password+"'");
            QString userName;

            // Keep searching username use the given id and password.
            while (qry.next())
                userName = qry.value("userName").toString();

            if (userName.isNull() || userName.isEmpty()) {
                QMessageBox::critical(this, "Error", "database hasn't userName");
                db.close();
                db.removeDatabase("C:/db/Client.db");
                return;
            }
            db.close();
            db.removeDatabase("C:/db/Client.db");
            hide();
            messenger = new MessengerWindow(userID, this);
            messenger->show();
        } else {
            QMessageBox::warning(this, "warning", "Id and password is not match");
            db.close();
            db.removeDatabase("C:/db/Client.db");
            return;
        }

    }
}

bool ClientSign::user_search(const QString &userID, const QString &password)
{
    QSqlQuery query;
    query.prepare("select * from ClientInfo where userID = '"+userID+"' and password='"+password+"'");
    query.exec();

    while(query.next())
        return true;
    return false;
}

// If user pressed SignUp Button!
void ClientSign::on_pushButton_signup_clicked()
{
	ClientSignUp clientSignUp;
	clientSignUp.setModal(true);
	clientSignUp.exec();
}
