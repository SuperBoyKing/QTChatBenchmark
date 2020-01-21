#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "centralserver.h"
#include "serverworker.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDebug>
#include <QtWidgets>
#include <QVector>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWindow)
    , m_centralServer(new CentralServer(this))
    , m_userModel(new QStandardItemModel(this))
    , m_serverWorker(new ServerWorker(this))
{
    ui->setupUi(this);
    this->setFixedSize(600, 700);
    m_userModel->insertColumn(0);
    ui->listView_userList->setModel(m_userModel);
    connect(m_centralServer, &CentralServer::logMessage, this, &ServerWindow::logMessage);
    connect(m_serverWorker, &ServerWorker::logMessage, this, &ServerWindow::logMessage);
    connect(m_centralServer, &CentralServer::userJoin, this, &ServerWindow::userJoin);
    connect(m_centralServer, &CentralServer::userLeft, this, &ServerWindow::userLeft);
    connect(ui->lineEdit_chat, &QLineEdit::returnPressed, this, &ServerWindow::sendMessage);
    connect(ui->pushButton_send, &QPushButton::clicked, this, &ServerWindow::sendMessage);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_pushButton_startServer_clicked()
{
    if (m_centralServer->isListening()) {
        m_centralServer->stopServer();
        ui->pushButton_startServer->setText(tr("Start Server"));
        logMessage(QString("Server Stopped"));
    } else {
        if (!m_centralServer->listen(QHostAddress::Any, 1997)) {
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));
            return;
        }
        logMessage(QString("Server Started"));
        ui->pushButton_startServer->setText("Stop Server");
    }
}

void ServerWindow::sendMessage()
{
    QString message = ui->lineEdit_chat->text();
    // using client to send the message that the user typed
    m_centralServer->serverSendMessage(message);
    ui->lineEdit_chat->clear();
    logMessage("Server send message: " + message);
}

void ServerWindow::logMessage(const QString &msg)
{
    ui->plainTextEdit_log->appendPlainText(msg + '\n');
}

void ServerWindow::userJoin(const QString &userID)
{
    const int newRow = m_userModel->rowCount();
    m_userModel->insertRow(newRow);
    m_userModel->setData(m_userModel->index(newRow, 0), userID);
    m_userModel->setData(m_userModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->listView_userList->scrollToBottom();
}

void ServerWindow::userLeft(const QString &userID)
{
    if (userID.isEmpty())
        return;

    // Remove name one of the userList when user left out of server.
    QList<QStandardItem *> items = m_userModel->findItems(userID, Qt::MatchExactly);
    m_userModel->takeRow(items.at(0)->row());
    delete items.at(0);

    if (items.isEmpty())
        return;
}
