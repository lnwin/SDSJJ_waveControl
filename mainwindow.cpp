#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <socket.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       ui->setupUi(this);
       qDebug()<<"main thread"<<QThread::currentThread();
       wave_thread =new QThread();
       waveSocket =new socket_SYS(ui);
       waveChart=new myChart(ui);
       connect(this,SIGNAL(socketInit()),waveSocket,SLOT (socket_Int()));
       connect(this,SIGNAL(sendMSG()),waveSocket,SLOT (wave_socket_SendMSG()));
       waveSocket->moveToThread(wave_thread);
       wave_thread->start();

       emit socketInit();

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
