/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QPushButton *pushButton_startServer;
    QListView *listView_userList;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_chat;
    QPushButton *pushButton_send;
    QPlainTextEdit *plainTextEdit_log;

    void setupUi(QWidget *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QString::fromUtf8("ServerWindow"));
        ServerWindow->resize(600, 700);
        pushButton_startServer = new QPushButton(ServerWindow);
        pushButton_startServer->setObjectName(QString::fromUtf8("pushButton_startServer"));
        pushButton_startServer->setGeometry(QRect(10, 10, 581, 31));
        listView_userList = new QListView(ServerWindow);
        listView_userList->setObjectName(QString::fromUtf8("listView_userList"));
        listView_userList->setGeometry(QRect(400, 50, 191, 601));
        listView_userList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layoutWidget = new QWidget(ServerWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 660, 581, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_chat = new QLineEdit(layoutWidget);
        lineEdit_chat->setObjectName(QString::fromUtf8("lineEdit_chat"));

        horizontalLayout->addWidget(lineEdit_chat);

        pushButton_send = new QPushButton(layoutWidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));

        horizontalLayout->addWidget(pushButton_send);

        plainTextEdit_log = new QPlainTextEdit(ServerWindow);
        plainTextEdit_log->setObjectName(QString::fromUtf8("plainTextEdit_log"));
        plainTextEdit_log->setEnabled(true);
        plainTextEdit_log->setGeometry(QRect(10, 50, 381, 601));
        plainTextEdit_log->setReadOnly(true);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QWidget *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "ServerWindow", nullptr));
        pushButton_startServer->setText(QApplication::translate("ServerWindow", "Start Server", nullptr));
        pushButton_send->setText(QApplication::translate("ServerWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
