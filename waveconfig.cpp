#include "waveconfig.h"
#include "ui_waveconfig.h"

waveConfig::waveConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waveConfig)
{
    ui->setupUi(this);
}

waveConfig::~waveConfig()
{
    delete ui;
}
