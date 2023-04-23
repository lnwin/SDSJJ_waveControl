#ifndef LOCALLOG_H
#define LOCALLOG_H

#include <QWidget>

namespace Ui {
class LocalLog;
}

class LocalLog : public QWidget
{
    Q_OBJECT

public:
    explicit LocalLog(QWidget *parent = nullptr);
    ~LocalLog();

private:
    Ui::LocalLog *ui;


public slots:
    void receiveMSG(QString);
signals:
    void closeWidget();
private slots:
    void on_pushButton_clicked();
};

#endif // LOCALLOG_H
