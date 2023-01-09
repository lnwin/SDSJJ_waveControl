#include "socket.h"
#include <QMessageBox>
bool severStatus=false;
bool ISconnected_0=false;
bool ISconnected_1=false;

socket_SYS::socket_SYS(QObject *parent) : QObject(parent)
{
    qDebug()<<"socket_SYS thread"<<QThread::currentThread();
}

socket_SYS::socket_SYS(Ui::MainWindow *ui)
{
    mui=ui;

}
void socket_SYS::socket_Int()
{
    mainServer = new QTcpServer();
    waveClient = new QTcpSocket();
    CRC =new crc();
    socket_Listening();
    qDebug()<<"socket_Int thread"<<QThread::currentThread();

}
bool socket_SYS::socket_Listening()
{
  //int port = 8087;  监听控制的端口号
    int port = 8088; //监听波形的端口号

    if(!mainServer->isListening())
    {
       if(mainServer->listen(QHostAddress("192.168.1.100"), port))
       //if(mainServer->listen(QHostAddress("10.16.50.16"), port))
        {
         // ui->textEdit->append("TCP_Sever is listeing");
         // ui->PortButton->setText("Stop Listen");
         // ui->Net_light->setStyleSheet("border-image: url(:/new/icon/picture/yellow.png);");
            connect(mainServer, SIGNAL(newConnection()), this, SLOT(server_New_Connect()));
         // connect(mainServer, SIGNAL(close()),this, SLOT(socket_SoptListening()));
         // qDebug()<<"mainServer listening ok";
            mui->textEdit->append(QStringLiteral("监听成功！"));
            return  true;
         }
       else
       {
          // ui->textEdit->append("Listening failed, Plesas change TCP_Sever IP to >>192.168.1.65<<!");
          // qDebug()<<"TCP_Sever listen failed, Plesas change TCP_Sever IP to >>192.168.1.65<<!";
           //qDebug()<<"Socket isListening thread"<<QThread::currentThread();
            mui->textEdit->append(QStringLiteral("监听失败, 请尝试将IP改为 >>192.168.1.100<<!"));
            return  false;

       }


     }

    else
    {
          mainServer->close();
          mui->textEdit->append(QStringLiteral("监听已关闭！"));
        // ui->PortButton->setText("Start Listen");
       //  ui->Net_light->setStyleSheet("border-image: url(:/new/icon/picture/gray.png);");
    }


}



bool socket_SYS::server_New_Connect()
{
    waveClient=mainServer->nextPendingConnection();//can not use twice;

           if(!waveClient)
           {
               mui->textEdit->append(QStringLiteral("声学网络连接失败！"));
               // qDebug()<<waveClient;
               return false;
           }
           else
           {
               mui->textEdit->append(QStringLiteral("声学网络连接成功！"));
               qDebug()<<waveClient->peerAddress();
               qDebug()<<waveClient->peerPort();
               connect(waveClient, SIGNAL(readyRead()), this, SLOT(wave_socket_Read_Data()));
               connect(waveClient, SIGNAL(disconnected()), this, SLOT(wave_socket_Disconnected()));
               return true;

           }






}

void socket_SYS::wave_socket_Read_Data()
{
    QByteArray waveData = waveClient->readAll();
    char *myData = waveData.data();
    QString str;
    str = QString::fromLocal8Bit(myData);

    if(noMode)
    {
        QString strHead;
        strHead=str.left(5);
        if(strHead=="$$$$$")
        {
           mui->textEdit->append(QStringLiteral("开始接收实时波形数据"));
           mui->textEdit->update();
           isCurrentData=true;
           noMode=false;
           if(str.size()>10)
           {
               str.remove(0,7);
               currentdataStream+=str;
           }

        }
        else if (strHead=="#####")
        {
            mui->textEdit->append(QStringLiteral("开始接收波形文件"));
            mui->textEdit->update();
            isFileData=true;
            noMode=false;
            if(str.size()>10)
            {
                str.remove(0,7);
                filsedataStream+=str;
            }

        }

    }

    else
    {
         QString strTips;
         strTips=str.right(7);
        if(isCurrentData)
        {
               qDebug()<<strTips;
            currentdataStream+=str;
           // if(strTips=="&&&&&\r\n") 实际使用
            if(strTips=="&&&\\r\\n")//本地测试用
            {
                isCurrentData=false;
                noMode=true;
                mui->textEdit->append(QStringLiteral("实时波形接收结束"));
                mui->textEdit->update();
                QString finalcurrentdataStream=currentdataStream.remove(currentdataStream.indexOf("&"),9);//本地测试是9，实际需要改
                analyzeCurrentData(finalcurrentdataStream);
                currentdataStream.clear();
            }
        }
        else if (isFileData)
        {
            filsedataStream+=str;
            // if(strTips=="&&&&&\r\n") 实际使用
             if(strTips=="&&&&&\r\n")//本地测试用
            {
                isCurrentData=false;
                noMode=true;
                mui->textEdit->append(QStringLiteral("波形文件接收结束"));
                mui->textEdit->update();
                QString finalfilsedataStream=filsedataStream.remove(filsedataStream.indexOf("&"),7);
                filsedataStream.clear();
            }

        }
    }



//    QByteArray waveDataC1;is
//    waveDataC1[0]= waveData.at(6);
//    waveDataC1[1]= waveData.at(7);
//    int C1=waveDataC1.toHex().toInt(0,16);
//    QByteArray waveDataforcheck=waveData.remove(6,2);
//    uint16_t C2=CRC->ModbusCRC16(waveDataforcheck);



}
void socket_SYS::wave_socket_Disconnected()
{
     mui->textEdit->append(QStringLiteral("声学网络已断开！"));
}
//void socket_SYS::control_socket_Read_Data()
//{
////    QByteArray controlData = controlClient->readAll();
////    QByteArray controlDataC1;
////    controlDataC1[0]= controlData.at(31);
////    controlDataC1[1]= controlData.at(32);
////    int C1=controlDataC1.toHex().toInt(0,16);

////    QByteArray controlDataforcheck=controlData.mid(0,31);
////    uint16_t C2=CRC->ModbusCRC16(controlDataforcheck);
////    QVariantList val;

////    if(C1==C2)
////    {

////         float RollAngle=(float(controlData.mid(2,2).toHex().toInt(0,16)*180)/32768);
////         val.append(RollAngle);

////         float PitchAngle=(float(controlData.mid(4,2).toHex().toInt(0,16))*180)/32768;
////         val.append(PitchAngle);
////         float YawAngle=(float(controlData.mid(6,2).toHex().toInt(0,16))*180)/32768;
////         val.append(YawAngle);
////         float Depth =controlData.mid(8,2).toHex().toInt(0,16)*1000;//单位毫米
////               Depth +=controlData.mid(10,2).toHex().toInt(0,16);
////               val.append(Depth);
////               qDebug()<<"Depth========="<<Depth;
////         float Tofloor =controlData.mid(12,2).toHex().toInt(0,16)*1000;//单位毫米
////               Tofloor+=controlData.mid(13,1).toHex().toInt(0,16);//单位毫米
////               val.append(Tofloor);
////               qDebug()<<"Tofloor========="<<Tofloor;
////         float ArmAngle= controlData.mid(15,2).toHex().toInt(0,16)*0.01;//单位毫米
////         val.append(ArmAngle);
////         qDebug()<<"ArmAngle========="<<ArmAngle;
////         float TGMoveLength =float(float(controlData.mid(17,2).toHex().toInt(0,16))-819)*500/(4095-819);//单位毫米
////         val.append(TGMoveLength);
////          qDebug()<<"TGMoveLength= ORIGIN========"<<controlData.mid(17,2).toHex().toInt(0,16);
////         qDebug()<<"TGMoveLength========="<<TGMoveLength;
////         float ArmMoveLength =float(float(controlData.mid(19,2).toHex().toInt(0,16))-819)*500/(4095-819);//单位毫米
////         val.append(ArmMoveLength);

////         qDebug()<<"ArmMoveLength========="<<ArmMoveLength;
////         float ArmPress =float(float(controlData.mid(21,2).toHex().toInt(0,16))-819)*250/(4095-819);//单位bar
////         val.append(ArmPress);
////         qDebug()<<"ArmPress========="<<ArmPress;
////         float YYPress =float(float(controlData.mid(23,2).toHex().toInt(0,16))-819)*250/(4095-819);//单位bar
////         val.append(YYPress);
////         qDebug()<<"YYPress========="<<YYPress;
////         emit sendcontrolMSG2T(val);
////    }

////    else
////   {

////      // qDebug()<<"CRC faile";
////       emit sendSocketState2T(QStringLiteral("CRC校验失败！\n"));

////   }



QByteArray socket_SYS::readUIParameter(int type)
{
    QByteArray UIParameter;
    UIParameter.resize(13);

     UIParameter[0]=mui->emissionN->currentIndex()+1 ;
     UIParameter[1]=int(mui->emissionVoltage->text().toFloat()*10);
     UIParameter[2]=mui->waveformCyclesN->text().toInt();
     UIParameter[3]=int(mui->emissionFrequency->text().toFloat()*10);
     UIParameter[4]=mui->emissionWavePool->currentIndex()+1;
     UIParameter[5]=mui->emissionInterval->text().toInt();
     UIParameter[6]=mui->emissionCount->text().toInt();
     UIParameter[7]=mui->amplingLength->text().toInt();
     UIParameter[8]=mui->amplingFrequency->currentIndex()+1;
     UIParameter[9]=mui->gainMultiplier->text().toInt();
     UIParameter[10]=mui->waveGetStart->text().toInt();
     UIParameter[11]=mui->waveGetEnd->text().toInt();
     UIParameter[12]=type;
    // UIParameter.resize(sizeof(UIParameterF));
    // memcpy(UIParameter.data(), &UIParameterF, sizeof(UIParameter));
     return UIParameter;

};
void socket_SYS::wave_socket_SendMSG()
{

    uint16_t C3=CRC->ModbusCRC16(readUIParameter(1));
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(readUIParameter(1));
    qDebug()<<"MSG.toHex()"<<MSG.toHex();
    waveClient->write(MSG);

};

void socket_SYS::startSample()
{
    QByteArray ORG;
    ORG.resize(2);
    ORG[0]=0x01;
    ORG[1]=0x02;
    uint16_t C3=CRC->ModbusCRC16(ORG);
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(ORG);
    waveClient->write(MSG);

}

void socket_SYS::receiveFilePath(QString filePath)
{
    myFilePath = filePath;
}

void socket_SYS::analyzeCurrentData(QString cd)
{
    QList<double>channal_1;
    QList<double>channal_2;
    QList<QString>cdList=cd.split(" ");
    //qDebug()<<"cdList"<<cdList;
    bool ok;
    int countN=cdList.size()/2;
     for(int i=0;i<countN;i++)
     {
        channal_1.append(cdList[i*2].toDouble(&ok));
        channal_2.append(cdList[(i*2)+1].chopped(4).toDouble(&ok));//本地测试是4，实际需要改
     }


//    qDebug()<<"channal_1"<<channal_1;
//    qDebug()<<"channal_2"<<channal_2;
}
void socket_SYS::saveFileData(QString fd)
{

};


