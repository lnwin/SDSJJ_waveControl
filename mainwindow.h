#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <socket.h>
#include <QMainWindow>
#include <QThread>
#include <mychart.h>
#include <qfiledialog.h>
#include <waveconfig.h>
#include <locallog.h>
#include <selectsavepath.h>
#include <readfile.h>
#include <QTimer>
#include <savethread.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//new
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QThread *waveSocketThread ;
    QThread *waveChartThread ;
    QThread *savethreadThread;
    myChart *waveChart;
    socket_SYS *waveSocket;
    waveConfig *WC;
    LocalLog *myLocal;
    selectSavePath *myselectSavePath;
    readfile *myreadfile;
    QTimer* mytimer;
    savethread*mysavethread;


 bool needLog=false;

 signals:
    void socketInit();
    void chartInit();
    void sendMSG();
    void sendMSGXL();
    void startSample();
    void sendFilePath(QString);
    void sendDestroy();
    void readConfig();
    void closeSoundPower();
    void openSoundPower();
    void sendNeedLogFlag(bool);
    void sendUIlock();


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
    void on_pushButton_9_clicked();
    void openLocalLog();
public slots:
    void receiveUIlock(bool);

    void on_pushButton_8_clicked();
    void on_waveformCyclesN_editingFinished();

    void on_emissionCount_editingFinished();

    void on_emissionInterval_editingFinished();

    void on_pushButton_10_clicked();
    void on_readfile_clicked();

    //void testcycle();
private:
    Ui::MainWindow *ui;
    QString  srcDirPath;
};
#endif // MAINWINDOW_H
