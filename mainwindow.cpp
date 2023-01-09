#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <socket.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       ui->setupUi(this);
       qDebug()<<"main thread"<<QThread::currentThread();
       waveSocketThread =new QThread();
       waveChartThread=new QThread();
       waveSocket =new socket_SYS(ui);
       waveChart=new myChart(ui);
       connect(this,SIGNAL(socketInit()),waveSocket,SLOT (socket_Int()));
       connect(this,SIGNAL(sendMSG()),waveSocket,SLOT (wave_socket_SendMSG()));
       connect(this,SIGNAL(startSample()),waveSocket,SLOT (startSample()));
       connect(this,SIGNAL(sendFilePath(QString)),waveSocket,SLOT (receiveFilePath(QString)));
       waveSocket->moveToThread(waveSocketThread);
       waveSocketThread->start();
       emit socketInit();
       waveChart->moveToThread(waveChartThread);
       waveChartThread->start();
       connect(this,SIGNAL(chartInit()),waveChart,SLOT (chart_Init()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    emit sendMSG();
}


void MainWindow::on_pushButton_2_clicked()
{

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

