#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <crc.h>
#include <QThread>
#include <ui_mainwindow.h>
//#include <mystruct.h>
#include <QDebug>
#include <QFile>
#include <QTime>
#include <QDateTime>
#include <QMessageBox>
class socket_SYS : public QObject
{
    Q_OBJECT
public:
    explicit socket_SYS(QObject *parent = nullptr);
     ~socket_SYS();
    socket_SYS(Ui::MainWindow *ui);
    QTcpServer *mainServer;
    QTcpSocket *waveClient;
//    Q_INVOKABLE    void socket_Int();
//    Q_INVOKABLE    bool socket_Listening();
    crc *CRC;
    QThread *socketThread;

    Ui::MainWindow *mui;
    QByteArray readUIParameter(int type);
signals:
  void sendSocketState2T(QString);
  void sendcontrolMSG2T(QVariantList val);
  void sendData2Chart(QList<double>C1,QList<double>C2,QList<QString>range);
  void sendCallBack();
  void sendConfig2M(QList<QString>);
  void sendMSG2Log(QString);

  void sendUIlock(bool);

public slots:
    void socket_Int();
    bool socket_Listening();
    bool server_New_Connect();
    void wave_socket_Read_Data();
    void wave_socket_Disconnected();
    void wave_socket_SendMSG();
    void startSample();
    void receiveFilePath(QString);
    void closeMySocket();
    void receivedMutlOrder(QList<QList<int>>);
    void readMyConfig();
    void closeSoundPower();
    void openSoundPower();
    void receivedNeedLogFlag(bool);
    void shutDownFLag();

private slots:


    void on_pushButton_clicked();




private:

    QString myFilePath ="D:/waveFiles";
    bool noMode=true;
    bool isCurrentData=false;
    bool isFileData=false;
    QString currentdataStream;
    QString filsedataStream;
    QString Range;
    QString fileKeyMSG;
    void analyzeCurrentData(QString,QString);
    void saveFileData(QString);
    QList<QString>configMSG;
    bool needLog();
    bool needLogFlag=false;
    bool isSendpushed=false;
    bool isSending=false;

};

#endif // SOCKET_H
