/********************************************************************************
** Form generated from reading UI file 'clientsign.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTSIGN_H
#define UI_CLIENTSIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientSign
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_userId;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_password;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_signin;
    QPushButton *pushButton_signup;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientSign)
    {
        if (ClientSign->objectName().isEmpty())
            ClientSign->setObjectName(QString::fromUtf8("ClientSign"));
        ClientSign->resize(582, 450);
        centralWidget = new QWidget(ClientSign);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(120, 20, 341, 281));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_userId = new QLineEdit(groupBox);
        lineEdit_userId->setObjectName(QString::fromUtf8("lineEdit_userId"));

        horizontalLayout->addWidget(lineEdit_userId);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_password);


        verticalLayout->addLayout(horizontalLayout_2);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 320, 341, 71));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_signin = new QPushButton(layoutWidget);
        pushButton_signin->setObjectName(QString::fromUtf8("pushButton_signin"));

        horizontalLayout_3->addWidget(pushButton_signin);

        pushButton_signup = new QPushButton(layoutWidget);
        pushButton_signup->setObjectName(QString::fromUtf8("pushButton_signup"));

        horizontalLayout_3->addWidget(pushButton_signup);

        ClientSign->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientSign);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 582, 26));
        ClientSign->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClientSign);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ClientSign->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ClientSign);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ClientSign->setStatusBar(statusBar);

        retranslateUi(ClientSign);

        QMetaObject::connectSlotsByName(ClientSign);
    } // setupUi

    void retranslateUi(QMainWindow *ClientSign)
    {
        ClientSign->setWindowTitle(QApplication::translate("ClientSign", "ClientSign", nullptr));
        groupBox->setTitle(QApplication::translate("ClientSign", "SignIn", nullptr));
        label->setText(QApplication::translate("ClientSign", "UserID    ", nullptr));
        label_2->setText(QApplication::translate("ClientSign", "Password", nullptr));
        pushButton_signin->setText(QApplication::translate("ClientSign", "SignIn", nullptr));
        pushButton_signup->setText(QApplication::translate("ClientSign", "SignUp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientSign: public Ui_ClientSign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTSIGN_H
