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
void LocalLog::receiveMSG(QString msg)
{
  ui->textEdit->append(msg);
}

void LocalLog::on_pushButton_clicked()
{
    ui->textEdit->clear();
}

