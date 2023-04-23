﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <socket.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       ui->setupUi(this);

       //this->model = new QStandardItemModel;   //创建一个标准的条目模型
       qDebug()<<"main thread"<<QThread::currentThread();
       waveSocketThread =new QThread();
       waveChartThread=new QThread();
       waveSocket =new socket_SYS(ui);
       WC=new waveConfig();
       waveChart=new myChart();
       myLocal=new LocalLog();
       waveChart->chart_Init(ui);
       connect(this,SIGNAL(socketInit()),waveSocket,SLOT (socket_Int()));
       connect(this,SIGNAL(sendMSG()),waveSocket,SLOT (wave_socket_SendMSG()));
       connect(this,SIGNAL(startSample()),waveSocket,SLOT (startSample()));
       connect(this,SIGNAL(sendDestroy()),waveSocket,SLOT (closeMySocket()));
       connect(this,SIGNAL(readConfig()),waveSocket,SLOT (readMyConfig()));
       connect(this,SIGNAL(sendFilePath(QString)),waveSocket,SLOT (receiveFilePath(QString)));

       connect(this,SIGNAL(closeSoundPower()),waveSocket,SLOT (closeSoundPower()));
       connect(this,SIGNAL(openSoundPower()),waveSocket,SLOT (openSoundPower()));

       connect(waveSocket,SIGNAL(sendCallBack()),this,SLOT (receiveCallBack()));
       connect(waveSocket,SIGNAL(sendConfig2M(QList<QString>)),this,SLOT (receiveConfigMSG(QList<QString>)));


       connect(WC,SIGNAL(sendMSG2(QList<QList<int>>)),waveSocket,SLOT (receivedMutlOrder(QList<QList<int>>)));
       waveSocket->moveToThread(waveSocketThread);
       waveSocketThread->start();
       connect(waveSocket,SIGNAL(sendData2Chart(QList<double>,QList<double>,QList<QString>)),waveChart,SLOT (chartUpdate(QList<double>,QList<double>,QList<QString>)));
       emit socketInit();

       connect(ui->actionbackground,SIGNAL(triggered()),this,SLOT(openLocalLog()));

       connect(this,SIGNAL(sendNeedLogFlag(bool)),waveSocket,SLOT(receivedNeedLogFlag(bool)));

       connect(waveSocket,SIGNAL(sendMSG2Log(QString)),myLocal,SLOT(receiveMSG(QString)));

       connect(myLocal,SIGNAL(closeWidget()),waveSocket,SLOT(shutDownFLag()));



}


void MainWindow::openLocalLog()
{
    if(!needLog)
    {
         myLocal->show();
         needLog=true;
         emit sendNeedLogFlag(needLog);
    }

    else
    {
        myLocal->hide();
        needLog=false;
        emit sendNeedLogFlag(needLog);
    }

}

MainWindow::~MainWindow()
{
    emit sendDestroy();
    delete ui;

}
void MainWindow::on_pushButton_clicked()
{
    emit sendMSG();
}


void MainWindow::on_pushButton_2_clicked()
{
    emit readConfig();
}
void MainWindow::on_gainMultiplier_editingFinished()
{
     if(ui->gainMultiplier->text().toInt()>255 )
     {
         QMessageBox msgBox;
         msgBox.setText("数值需小于255");
         msgBox.exec();
         ui->gainMultiplier->setText("");
     }
}
void MainWindow::on_amplingLength_editingFinished()
{
     if(ui->amplingLength->text().toInt()>128 )
     {
         QMessageBox msgBox;
         msgBox.setText("数值需小于128");
         msgBox.exec();
         ui->amplingLength->setText("");
     }
}
void MainWindow::on_waveGetStart_editingFinished()
{
    if(ui->waveGetStart->text().toInt()>128 )
    {
        QMessageBox msgBox;
        msgBox.setText("数值需小于128");
        msgBox.exec();
        ui->waveGetStart->setText("");
    }
    if(ui->waveGetStart->text().toInt()<0)
    {
        QMessageBox msgBox;
        msgBox.setText("数值需大于0");
        msgBox.exec();
        ui->waveGetStart->setText("");
    }
}
void MainWindow::on_waveGetEnd_editingFinished()
{
    if(ui->waveGetEnd->text().toInt()<ui->waveGetStart->text().toInt() )
    {
        QMessageBox msgBox;
        msgBox.setText("数值需大于开始值");
        msgBox.exec();
        ui->waveGetEnd->setText("");
    }
    if(ui->waveGetEnd->text().toInt()>ui->amplingLength->text().toInt())
    {
        QMessageBox msgBox;
        msgBox.setText("数值不得大于采样长度");
        msgBox.exec();
        ui->waveGetEnd->setText("");
    }
}

void MainWindow::on_startSample_clicked()
{
    emit startSample();
}
void MainWindow::on_fileSaveButton_clicked()
{
    srcDirPath = QFileDialog::getExistingDirectory( this, "Rec path", "/");
       if (srcDirPath.isEmpty())
       {
           return;
       }
       else
       {
           ui->fileStream->setText(srcDirPath);
           emit sendFilePath(srcDirPath);

       }
}
  void MainWindow::receiveCallBack()
  {
      QMessageBox msgBox;
      msgBox.setWindowTitle("接收反馈");
      msgBox.setText("指令下发成功！");
      msgBox.exec();
  }
  void MainWindow::on_pushButton_4_clicked()
  {
    WC->show();
  }
void MainWindow::receiveConfigMSG(QList<QString> mylist)
{
    QDateTime time = QDateTime::currentDateTime();
    QString myTime =time.toString("yyyy-MM-dd hh:mm:ss")+"\r";
    QString myMsG;
    myMsG="当前配置---发射通道："+mylist[0]+"  发射电压："+mylist[1]+"v  循环周期："+mylist[2]+"次  发射频率："+mylist[3]+"kHZ  发射波形："+mylist[4]
            +"  发射间隔："+mylist[5]+"秒  发射次数："+mylist[6]+"  采样长度："+mylist[7]+"K  采样频率："+mylist[8]+"  增益系数："+mylist[9]+"  采样起点："+mylist[10]+"K  采样终点："+mylist[11]+"K";
    myTime+=myMsG;
    ui->readParameter->setText(myTime);
};
void MainWindow::on_pushButton_3_clicked()
{
   // void closeSoundPower();
    emit openSoundPower();
}
void MainWindow::on_pushButton_6_clicked()
{
     emit closeSoundPower();
}

void MainWindow::on_pushButton_5_clicked()
{
    emit openSoundPower();
}


void MainWindow::on_pushButton_7_clicked()
{
    emit closeSoundPower();
}
