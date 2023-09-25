#include "selectsavepath.h"
#include "ui_selectsavepath.h"
#include <QFileDialog>
selectSavePath::selectSavePath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectSavePath)
{
    ui->setupUi(this);
}

selectSavePath::~selectSavePath()
{
    delete ui;
}

void selectSavePath::on_pushButton_clicked()
{
  QString  srcDirPath = QFileDialog::getExistingDirectory( this, "Rec path", "/");
     if (srcDirPath.isEmpty())
     {
         return;
     }
     else
     {
                ui->filepath->setText(srcDirPath);
     }
}


void selectSavePath::on_pushButton_2_clicked()
{
     emit sendSaveMSG(ui->filename->text(), ui->filepath->text() );
}


void selectSavePath::on_pushButton_3_clicked()
{
    this->hide();
}

