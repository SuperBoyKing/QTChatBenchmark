#ifndef FILESELECTER_H
#define FILESELECTER_H

#include <QObject>
#include <QWidget>

class FileSelecter : public QWidget
{
    Q_OBJECT
public:
    explicit FileSelecter(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // FILESELECTER_H
