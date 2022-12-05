#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <socket.h>
#include <QMainWindow>
#include <QThread>
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

    socket_SYS *waveSocket;

 signals:
    void socketInit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
