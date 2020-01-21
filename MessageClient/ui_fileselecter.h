/********************************************************************************
** Form generated from reading UI file 'fileselecter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESELECTER_H
#define UI_FILESELECTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QListWidget *listWidget_fileList;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_download;
    QPushButton *pushButton_cancle;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(584, 479);
        listWidget_fileList = new QListWidget(Form);
        listWidget_fileList->setObjectName(QString::fromUtf8("listWidget_fileList"));
        listWidget_fileList->setGeometry(QRect(50, 20, 491, 401));
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 420, 491, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_download = new QPushButton(widget);
        pushButton_download->setObjectName(QString::fromUtf8("pushButton_download"));

        horizontalLayout->addWidget(pushButton_download);

        pushButton_cancle = new QPushButton(widget);
        pushButton_cancle->setObjectName(QString::fromUtf8("pushButton_cancle"));

        horizontalLayout->addWidget(pushButton_cancle);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        pushButton_download->setText(QApplication::translate("Form", "Download", nullptr));
        pushButton_cancle->setText(QApplication::translate("Form", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESELECTER_H
