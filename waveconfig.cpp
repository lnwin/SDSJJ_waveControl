#include "waveconfig.h"
#include "ui_waveconfig.h"

waveConfig::waveConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waveConfig)
{
    ui->setupUi(this);
    TVmodel = new QStandardItemModel();
    this->ui->tableView->setModel(TVmodel);
    modelinit();

}
void waveConfig::modelinit()
{
    // set columns
        QStringList columnTitles;
        columnTitles  << "发射波形" << "发射频率(KHz)" << "发射电压(v)"<< "发射电压"<< "波形周期数"<< "发射换能器通道"<< "发射间隔(s)"<< "发射次数";
        TVmodel->setHorizontalHeaderLabels(columnTitles);
        this->ui->tableView->setColumnWidth(0, 70);

};
waveConfig::~waveConfig()
{
    delete ui;
}

void waveConfig::on_addOrder_clicked()
{
    TVmodel->setItem(OrderIndex, 0, new QStandardItem(""));
    QComboBox* waveType = new QComboBox();
    waveType->addItems({"高斯波", "正弦波"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 0), waveType);
    TVmodel->setItem(OrderIndex, 1, new QStandardItem("null"));
    TVmodel->setItem(OrderIndex, 2, new QStandardItem("null"));
    TVmodel->setItem(OrderIndex, 3, new QStandardItem("null"));
    TVmodel->setItem(OrderIndex, 4, new QStandardItem("null"));


    QComboBox* channel = new QComboBox();
    channel->addItems({"1", "2", "3", "4", "5"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 5), channel);
    TVmodel->setItem(OrderIndex, 6, new QStandardItem("null"));
    TVmodel->setItem(OrderIndex, 7, new QStandardItem("null"));



     OrderIndex+=1;

}

void waveConfig::on_deleteOrder_clicked()
{
    auto index = ui->tableView->currentIndex();
    TVmodel->removeRow(index.row());
 // TVmodel->removeRow(OrderIndex);

}

void waveConfig::on_finishWrite_clicked()
{

}

void waveConfig::checkAllTable()
{

};


