#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <crc.h>
#include <QThread>
#include <ui_mainwindow.h>
//#include <mystruct.h>
class socket_SYS : public QObject
{
    Q_OBJECT
public:
    explicit socket_SYS(QObject *parent = nullptr);

    socket_SYS(Ui::MainWindow *ui);
    QTcpServer *mainServer;
    QTcpSocket *waveClient;
//    Q_INVOKABLE    void socket_Int();
//    Q_INVOKABLE    bool socket_Listening();
    crc *CRC;
    QThread *socketThread;

    Ui::MainWindow *mui;

signals:
  void sendSocketState2T(QString);
  void sendcontrolMSG2T(QVariantList val);
public slots:
    void socket_Int();
    bool socket_Listening();
    bool server_New_Connect();
    void wave_socket_Read_Data();
    void wave_socket_Disconnected();

private:


};

#endif // SOCKET_H
