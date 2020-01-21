#include "fileselecter.h"
#include "ui_fileselecter.h"
#include <QDir>
#include <QMessageBox>

FileSelecter::FileSelecter(QWidget *parent)
    : QObject(parent)
    , ui(new Ui::FileSelecter)
{

}
