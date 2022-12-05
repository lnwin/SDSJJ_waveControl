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
       connect(this,SIGNAL(socketInit()),waveSocket,SLOT (socket_Int()));
       waveSocket->moveToThread(wave_thread);
       wave_thread->start();

       emit socketInit();

}

MainWindow::~MainWindow()
{
    delete ui;
}

