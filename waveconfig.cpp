#include "waveconfig.h"
#include "ui_waveconfig.h"
#include <QDebug>
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
 columnTitles  << "发射波形" << "发射频率(KHz)" <<"发射电压"<<"波形周期数"<< "发射换能器通道"<<"发射间隔(s)"<<"发射次数"<<"采样频率(MSPS)"<<"接收增益"<<"参考增益"<<"采样长度(K)"<<"上传波形起点(k)"<<"上传波形终点(k)"<<"功放功率(k)";
     TVmodel->setHorizontalHeaderLabels(columnTitles);
     this->ui->tableView->setColumnWidth(0, 70);

};
waveConfig::~waveConfig()
{
    delete ui;
}

void waveConfig::on_addOrder_clicked()
{

    QComboBox* waveType = new QComboBox();
    QComboBox* channel = new QComboBox();
    QComboBox* channel2 = new QComboBox();
    QComboBox* channel3 = new QComboBox();
    QComboBox* channel4 = new QComboBox();

    TVmodel->setItem(OrderIndex, 0, new QStandardItem(""));

    waveType->addItems({ "高斯波","正弦波" });
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 0), waveType);
    TVmodel->setItem(OrderIndex, 1, new QStandardItem("10"));
    TVmodel->setItem(OrderIndex, 2, new QStandardItem("0.5"));
    TVmodel->setItem(OrderIndex, 3, new QStandardItem("5"));


    channel->addItems({"1", "2", "3", "4", "5"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 4), channel);
    TVmodel->setItem(OrderIndex, 5, new QStandardItem("5"));
    TVmodel->setItem(OrderIndex, 6, new QStandardItem("1"));


    channel2->addItems({"5MHz", "10MHz", "15MHz", "20MHz"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 7), channel2);
    TVmodel->setItem(OrderIndex, 8, new QStandardItem("128"));
    TVmodel->setItem(OrderIndex, 9, new QStandardItem("10"));
    TVmodel->setItem(OrderIndex, 10, new QStandardItem("0"));
    TVmodel->setItem(OrderIndex, 11, new QStandardItem("10"));
    channel3->addItems({"低档", "中档", "高档"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 12), channel3);

    channel4->addItems({"1/8", "1/4", "3/8", "1/2", "5/8", "3/4", "7/8", "1"});
    ui->tableView->setIndexWidget(TVmodel->index(OrderIndex, 9), channel4);
     OrderIndex+=1;

}

void waveConfig::on_deleteOrder_clicked()
{
    auto index = ui->tableView->currentIndex();
    TVmodel->removeRow(index.row());
    OrderIndex-=1;

}

void waveConfig::on_finishWrite_clicked()
{

     this->hide();
     checkAllTable();

}

void waveConfig::checkAllTable()
{
    int orderCount;
    QList<QList<int>> orderList;
    orderCount=TVmodel->rowCount();

    for(int i=0;i<orderCount;i++)
    {
       QList<int> linshiList;
//       TVmodel->data(TVmodel->index(i,0)).toFloat() ; //发射波形
//       TVmodel->data(TVmodel->index(i,1));//发射频率
//       TVmodel->data(TVmodel->index(i,2));//发射电压
//       TVmodel->data(TVmodel->index(i,3));//波形周期数
//       TVmodel->data(TVmodel->index(i,4));//发射换能器通道
//       TVmodel->data(TVmodel->index(i,5));//发射间隔
//       TVmodel->data(TVmodel->index(i,6));//发射次数
//       TVmodel->data(TVmodel->index(i,7));//采样频率
//       TVmodel->data(TVmodel->index(i,8));//固定增益倍数
//       TVmodel->data(TVmodel->index(i,9));//采样长度
//       TVmodel->data(TVmodel->index(i,10));//上传波形起点
//       TVmodel->data(TVmodel->index(i,11));//上传波形终点

       QWidget *widgetQWidget1 =ui->tableView->indexWidget(TVmodel->index(i, 0));
       QComboBox *combox1=(QComboBox*)widgetQWidget1;
       QWidget *widgetQWidget2 =ui->tableView->indexWidget(TVmodel->index(i, 4));
       QComboBox *combox2=(QComboBox*)widgetQWidget2;
       QWidget *widgetQWidget3 =ui->tableView->indexWidget(TVmodel->index(i, 7));
       QComboBox *combox3=(QComboBox*)widgetQWidget3;
       QWidget *widgetQWidget4 =ui->tableView->indexWidget(TVmodel->index(i, 12));
       QComboBox *combox4=(QComboBox*)widgetQWidget4;
       QWidget *widgetQWidget5 =ui->tableView->indexWidget(TVmodel->index(i, 9));
            QComboBox *combox5=(QComboBox*)widgetQWidget5;

       linshiList.append(combox2->currentIndex()+1);//发射换能器通道
       linshiList.append(TVmodel->data(TVmodel->index(i,2)).toFloat()*10);//发射电压
       linshiList.append(TVmodel->data(TVmodel->index(i,3)).toInt());//波形周期数
       linshiList.append(TVmodel->data(TVmodel->index(i,1)).toFloat()*10);//发射频率
       linshiList.append(combox1->currentIndex()+1);//发射波形
       linshiList.append(TVmodel->data(TVmodel->index(i,5)).toInt());//发射间隔
       linshiList.append(TVmodel->data(TVmodel->index(i,6)).toInt());//发射次数
       linshiList.append(TVmodel->data(TVmodel->index(i,9)).toInt());//采样长度
       linshiList.append(combox3->currentIndex()+1);//采样频率

       linshiList.append(TVmodel->data(TVmodel->index(i,8)).toInt());//固定增益倍数
       linshiList.append(TVmodel->data(TVmodel->index(i,10)).toInt());//上传波形起点
       linshiList.append(TVmodel->data(TVmodel->index(i,11)).toInt());//上传波形终点
       linshiList.append(combox4->currentIndex()+1);//功放功率

       linshiList.append(combox5->currentIndex());//参考增益倍数


//       UIParameter[0]=mui->emissionN->currentIndex()+1;
//       UIParameter[1]=int(mui->emissionVoltage->text().toFloat()*10);
//       UIParameter[2]=mui->waveformCyclesN->text().toInt();
//       UIParameter[3]=int(mui->emissionFrequency->text().toFloat()*10);
//       UIParameter[4]=mui->emissionWavePool->currentIndex()+1;
//       UIParameter[5]=mui->emissionInterval->text().toInt();
//       UIParameter[6]=mui->emissionCount->text().toInt();
//       UIParameter[7]=mui->amplingLength->text().toInt();
//       UIParameter[8]=mui->amplingFrequency->currentIndex()+1;
//       UIParameter[9]=mui->gainMultiplier->text().toInt();
//       UIParameter[10]=mui->waveGetStart->text().toInt();
//       UIParameter[11]=mui->waveGetEnd->text().toInt();
//       UIParameter[12]=type;
        orderList.append(linshiList);

    }

    emit sendMSG2(orderList);
    //qDebug()<<"sendMSG2(orderList) "<<orderList;

};


