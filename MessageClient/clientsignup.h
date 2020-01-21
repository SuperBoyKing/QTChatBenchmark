#ifndef CLIENTSIGNUP_H
#define CLIENTSIGNUP_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class ClientSignUp;
}

class ClientSignUp : public QDialog
{
    Q_OBJECT

public:
    explicit ClientSignUp(QWidget *parent = nullptr);
    ~ClientSignUp();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ClientSignUp *ui;
};

#endif // CLIENTSIGNUP_H
