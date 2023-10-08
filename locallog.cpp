#include "locallog.h"
#include "ui_locallog.h"

LocalLog::LocalLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalLog)
{
    ui->setupUi(this);
}

LocalLog::~LocalLog()
{
    emit closeWidget();
    delete ui;
}
int count =0;
void LocalLog::receiveMSG(QString msg)
{


//        if(count>7)
//        {
//            ui->textEdit->clear();
//            count=0;
//        }

//        count+=1;
//        if(msg!="HEARTBEAT\r\n")
      ui->textEdit->append(msg);


}

void LocalLog::on_pushButton_clicked()
{
    ui->textEdit->clear();
}

