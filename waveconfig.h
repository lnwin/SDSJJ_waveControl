#ifndef WAVECONFIG_H
#define WAVECONFIG_H

#include <QDialog>

namespace Ui {
class waveConfig;
}

class waveConfig : public QDialog
{
    Q_OBJECT

public:
    explicit waveConfig(QWidget *parent = nullptr);
    ~waveConfig();

private:
    Ui::waveConfig *ui;
};

#endif // WAVECONFIG_H
