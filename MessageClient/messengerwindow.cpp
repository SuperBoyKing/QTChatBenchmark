#include "messengerwindow.h"
#include "ui_messengerwindow.h"
#include "chatclient.h"
#include "clientsign.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QHostAddress>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>

MessengerWindow::MessengerWindow(QString userID, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MessengerWindow)
    , m_chatClient(new ChatClient(this))
    , m_clientSign(new ClientSign(this))
    , m_chatModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    this->setFixedSize(530, 530);
    // the model for the messages will have 1 column
    m_chatModel->insertColumn(0);
    // set the model as the data source for the list view
    ui->listView_chatview->setModel(m_chatModel);
    // connect the signals from the chat client to the slots in this ui
    m_userID = userID;
    attemptConnection();

    connect(m_chatClient, &ChatClient::connected, this, &MessengerWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loginError, this, &MessengerWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &MessengerWindow::MessageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &MessengerWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &MessengerWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &MessengerWindow::userJoined);
    connect(m_chatClient, &ChatClient::userLeft, this, &MessengerWindow::userLeft);
    connect(ui->pushButton, &QPushButton::clicked, this, &MessengerWindow::sendMessage);
    connect(ui->lineEdit_chat, &QLineEdit::returnPressed, this, &MessengerWindow::sendMessage);
    connect(ui->toolButton_fileSend, &QPushButton::clicked, this, &MessengerWindow::sendFile);
}

MessengerWindow::~MessengerWindow()
{
    delete ui;
}

void MessengerWindow::attemptConnection()
{
    m_chatClient->connectToServer(QHostAddress("127.0.0.1"), 1997);
}

void MessengerWindow::connectedToServer()
{
    m_chatClient->login(m_userID);
}

void MessengerWindow::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    return m_chatClient->disconnectFromHost();
}

void MessengerWindow::MessageReceived(const QString &sender, const QString &text)
{
    // Store the index of the new row to append to the model containing the message
    int newRow = m_chatModel->rowCount();

    if ("Server" == sender) {
        // Create a bold default font
        QFont boldFont;
        boldFont.setBold(true);
        // Insert 2 row, one for the message and one for the username
        m_chatModel->insertRows(newRow, 2);
        // Store the username in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + ":");
        // Set the alignment for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignCenter | Qt::AlignVCenter), Qt::TextAlignmentRole);
        // Set the for the serverName
        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
        // Store the message in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), text);
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignCenter | Qt::AlignVCenter), Qt::TextAlignmentRole);

        // Display a line containing the username only if it's different from the last username displayed
    } else if (m_lastUserName != sender) {
        // store the last displayed username
        m_lastUserName = sender;
        // create a bold default font
        QFont boldFont;
        boldFont.setBold(true);
        // insert 2 row, one for the message and one for the username
        m_chatModel->insertRows(newRow, 2);
        // store the username in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + ':');
        // set the alignment for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::gray), Qt::ForegroundRole);
        // set the for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
        // store the message in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), text);
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    } else {
        // insert a row for the message
        m_chatModel->insertRow(newRow);
        // store the message in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), text);
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    }
    // store the message in the model
    ui->listView_chatview->scrollToBottom();
}

void MessengerWindow::sendMessage()
{
    // using client to send the message that the user typed
    m_chatClient->sendMessage(ui->lineEdit_chat->text());
    // now we add the message to the list
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    m_chatModel->insertRow(newRow);
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), ui->lineEdit_chat->text());
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    ui->lineEdit_chat->clear();
    // scroll the view to display the new message
    ui->listView_chatview->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void MessengerWindow::sendFile()
{
    QString filter = "All File (*.*) ;; Text File (*.txt) ;; XML File (*.xml)";
    QString fileName = QFileDialog::getOpenFileName(this, "select the file", QDir::homePath(), filter);

    if (fileName.isNull() || fileName.isEmpty())
       return;

    m_chatClient->sendFile(fileName);
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    m_chatModel->insertRow(newRow);
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 send file to the server").arg(m_userID));
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignCenter | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    ui->lineEdit_chat->clear();
    // scroll the view to display the new message
    ui->listView_chatview->scrollToBottom();
}

void MessengerWindow::userJoined(const QString &userID)
{
    // store the index of the new row to append to the model containing the message
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user joined
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Joined the Chat").arg(userID));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    // scroll the view to display the new message
    ui->listView_chatview->scrollToBottom();
    // reset the last printed userName
    m_lastUserName.clear();
}

void MessengerWindow::userLeft(const QString &userID)
{
    // store the index of the new row to append to the model containing the message
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user Left
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(userID));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    // scroll the view to display the new message
    ui->listView_chatview->scrollToBottom();
    // reset the last printed userName
    m_lastUserName.clear();
}

void MessengerWindow::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("the host terminated the connection"));
    ui->lineEdit_chat->setEnabled(false);
    ui->listView_chatview->setEnabled(false);
    ui->pushButton->setEnabled(false);
    m_lastUserName.clear();
}

void MessengerWindow::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        disconnectedFromServer();
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
}
