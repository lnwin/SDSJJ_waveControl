#ifndef WAVECONFIG_H
#define WAVECONFIG_H
#include <QComboBox>
#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class waveConfig;
}

class waveConfig : public QDialog
{
    Q_OBJECT

public:
    explicit waveConfig(QWidget *parent = nullptr);
    ~waveConfig();
public slots:

   // void receiveConfigMSG(QList<float>MSG);
signals:

    void sendMSG2(QList<QList<int>>);

private slots:
    void on_addOrder_clicked();

    void on_finishWrite_clicked();

    void on_deleteOrder_clicked();

private:
    Ui::waveConfig *ui;
    QStandardItemModel* TVmodel;
    void modelinit();
    int OrderIndex=0;
//    QComboBox* waveType = new QComboBox();
//     QComboBox* channel = new QComboBox();
//     QComboBox* channel2 = new QComboBox();

    void checkAllTable();
};

#endif // WAVECONFIG_H
