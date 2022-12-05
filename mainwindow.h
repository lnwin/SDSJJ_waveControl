#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <socket.h>
#include <QMainWindow>
#include <QThread>
#include <mychart.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QThread *wave_thread ;
    myChart *waveChart;
    socket_SYS *waveSocket;

 signals:
    void socketInit();
    void sendMSG();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_gainMultiplier_editingFinished();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
