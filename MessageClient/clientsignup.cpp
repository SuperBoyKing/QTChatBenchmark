#include "clientsignup.h"
#include "ui_clientsignup.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

ClientSignUp::ClientSignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientSignUp)
{
    ui->setupUi(this);
    this->setFixedSize(462, 368);
}

ClientSignUp::~ClientSignUp()
{
    delete ui;
}

// If user pressed SignUp!
void ClientSignUp::on_pushButton_register_clicked()
{
    const QString userID = ui->lineEdit_userID->text();
    const QString password = ui->lineEdit_password->text();
    const QString comfirm = ui->lineEdit_confirm->text();
    const QString userName = ui->lineEdit_name->text();

    if (userID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "please write your ID");
    } else if (userName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "please write your name");
    } else if (password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "please write your password");
    } else if (QString::compare(password, comfirm) != 0) {
        QMessageBox::warning(this, "Warning", "Not correct your password please check it");
    } else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/db/Client.db");
        QSqlQuery qry;

        if (!db.open()) {
            qDebug() << "problem opening database";
            return;
        }
        qry.setForwardOnly(true);
        qry.exec("select userID from ClientInfo");
        while (qry.next()) {
            QString Id = qry.value(0).toString();
            if (userID == Id) {
                QMessageBox::warning(this, "Warning", "Your set Id is duplicate in Database. please rename your ID");
                return;
            }
        }

        // This statements is perfrom password encryption using hash algorithm
        // and then convert QByteArray to utf-8
        QByteArray encryption = QCryptographicHash::hash(password.toLocal8Bit(),
                                QCryptographicHash::Keccak_256).toBase64();
        QString e_password = QString::fromUtf8(encryption);

        qry.prepare("INSERT INTO ClientInfo ("
                    "userID,"
                    "password,"
                    "userName)"
                    "VALUES (?, ?, ?)");
        qry.bindValue(0, userID);
        qry.bindValue(1, e_password);
        qry.bindValue(2, userName);
        qry.exec();
        QMessageBox::information(this, "Regist!", "You're now signup!");
        db.close();
        db.removeDatabase("C:/db/Client.db");
        hide();
    }
}


// If user pressed cancle!
void ClientSignUp::on_pushButton_cancel_clicked()
{
    hide();
}
