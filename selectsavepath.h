#ifndef SELECTSAVEPATH_H
#define SELECTSAVEPATH_H

#include <QDialog>

namespace Ui {
class selectSavePath;
}

class selectSavePath : public QDialog
{
    Q_OBJECT

public:
    explicit selectSavePath(QWidget *parent = nullptr);
    ~selectSavePath();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::selectSavePath *ui;
signals:
     void sendSaveMSG(QString filename,QString filepath);
};

#endif // SELECTSAVEPATH_H
