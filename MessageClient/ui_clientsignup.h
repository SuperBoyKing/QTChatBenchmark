/********************************************************************************
** Form generated from reading UI file 'clientsignup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTSIGNUP_H
#define UI_CLIENTSIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientSignUp
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_userID;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_password;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_confirm;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_register;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *ClientSignUp)
    {
        if (ClientSignUp->objectName().isEmpty())
            ClientSignUp->setObjectName(QString::fromUtf8("ClientSignUp"));
        ClientSignUp->resize(462, 368);
        groupBox = new QGroupBox(ClientSignUp);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 30, 371, 251));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_userID = new QLineEdit(groupBox);
        lineEdit_userID->setObjectName(QString::fromUtf8("lineEdit_userID"));

        horizontalLayout->addWidget(lineEdit_userID);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        horizontalLayout_3->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_confirm = new QLineEdit(groupBox);
        lineEdit_confirm->setObjectName(QString::fromUtf8("lineEdit_confirm"));
        lineEdit_confirm->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(lineEdit_confirm);


        verticalLayout->addLayout(horizontalLayout_4);

        layoutWidget = new QWidget(ClientSignUp);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 290, 351, 51));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton_register = new QPushButton(layoutWidget);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));

        horizontalLayout_5->addWidget(pushButton_register);

        pushButton_cancel = new QPushButton(layoutWidget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_5->addWidget(pushButton_cancel);


        retranslateUi(ClientSignUp);

        QMetaObject::connectSlotsByName(ClientSignUp);
    } // setupUi

    void retranslateUi(QWidget *ClientSignUp)
    {
        ClientSignUp->setWindowTitle(QApplication::translate("ClientSignUp", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("ClientSignUp", "SignUp", nullptr));
        label->setText(QApplication::translate("ClientSignUp", "UserID     ", nullptr));
        label_3->setText(QApplication::translate("ClientSignUp", "Name      ", nullptr));
        label_2->setText(QApplication::translate("ClientSignUp", "Password", nullptr));
        label_4->setText(QApplication::translate("ClientSignUp", "Confirm   ", nullptr));
        pushButton_register->setText(QApplication::translate("ClientSignUp", "Register", nullptr));
        pushButton_cancel->setText(QApplication::translate("ClientSignUp", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientSignUp: public Ui_ClientSignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTSIGNUP_H
