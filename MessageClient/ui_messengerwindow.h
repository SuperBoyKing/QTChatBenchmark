/********************************************************************************
** Form generated from reading UI file 'messengerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGERWINDOW_H
#define UI_MESSENGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessengerWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QListView *listView_chatview;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_fileSend;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_chat;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MessengerWindow)
    {
        if (MessengerWindow->objectName().isEmpty())
            MessengerWindow->setObjectName(QString::fromUtf8("MessengerWindow"));
        MessengerWindow->resize(531, 530);
        centralwidget = new QWidget(MessengerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 511, 511));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listView_chatview = new QListView(layoutWidget);
        listView_chatview->setObjectName(QString::fromUtf8("listView_chatview"));
        listView_chatview->setMouseTracking(false);
        listView_chatview->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(listView_chatview);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton_fileSend = new QToolButton(layoutWidget);
        toolButton_fileSend->setObjectName(QString::fromUtf8("toolButton_fileSend"));

        horizontalLayout_2->addWidget(toolButton_fileSend);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_chat = new QLineEdit(layoutWidget);
        lineEdit_chat->setObjectName(QString::fromUtf8("lineEdit_chat"));

        horizontalLayout->addWidget(lineEdit_chat);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        MessengerWindow->setCentralWidget(centralwidget);

        retranslateUi(MessengerWindow);

        QMetaObject::connectSlotsByName(MessengerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MessengerWindow)
    {
        MessengerWindow->setWindowTitle(QApplication::translate("MessengerWindow", "MainWindow", nullptr));
        toolButton_fileSend->setText(QApplication::translate("MessengerWindow", "Upload", nullptr));
        pushButton->setText(QApplication::translate("MessengerWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessengerWindow: public Ui_MessengerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGERWINDOW_H
