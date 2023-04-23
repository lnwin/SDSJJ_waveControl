#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <socket.h>
#include <QMainWindow>
#include <QThread>
#include <mychart.h>
#include <qfiledialog.h>
#include <waveconfig.h>
#include <locallog.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QThread *waveSocketThread ;
    QThread *waveChartThread ;
    myChart *waveChart;
    socket_SYS *waveSocket;
    waveConfig *WC;
    LocalLog *myLocal;

 bool needLog=false;

 signals:
    void socketInit();
    void chartInit();
    void sendMSG();
    void startSample();
    void sendFilePath(QString);
    void sendDestroy();
    void readConfig();
    void closeSoundPower();
    void openSoundPower();
    void sendNeedLogFlag(bool);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_gainMultiplier_editingFinished();
    void on_amplingLength_editingFinished();
    void on_waveGetStart_editingFinished();
    void on_waveGetEnd_editingFinished();

    void on_startSample_clicked();
    void on_fileSaveButton_clicked();
    void on_pushButton_4_clicked();
    void receiveCallBack();
    void receiveConfigMSG(QList<QString>);
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void openLocalLog();

private:
    Ui::MainWindow *ui;
    QString  srcDirPath;
};
#endif // MAINWINDOW_H
