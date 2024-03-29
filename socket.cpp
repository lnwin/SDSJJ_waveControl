﻿
#include "socket.h"
#include <QMessageBox>
#include <QTextStream>
#include <QTextCursor>
bool severStatus=false;
bool ISconnected_0=false;
bool ISconnected_1=false;

socket_SYS::socket_SYS(QObject *parent) : QObject(parent)
{
  //  qDebug()<<"socket_SYS thread"<<QThread::currentThread();
}
socket_SYS::~socket_SYS()
{

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
   // qDebug()<<"socket_Int thread"<<QThread::currentThread();

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
            QDateTime time = QDateTime::currentDateTime();
            QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"网络初始化成功!";
           // mui->textEdit->append(QStringLiteral("监听成功！"));
            mui->textEdit->append(mymsg);
            mui->textEdit->moveCursor(QTextCursor::Down);
            return  true;
         }
       else
       {
          // ui->textEdit->append("Listening failed, Plesas change TCP_Sever IP to >>192.168.1.65<<!");
          // qDebug()<<"TCP_Sever listen failed, Plesas change TCP_Sever IP to >>192.168.1.65<<!";
           //qDebug()<<"Socket isListening thread"<<QThread::currentThread();
            QDateTime time = QDateTime::currentDateTime();
            QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"网络初始化失败, 请尝试将IP改为 >>192.168.1.100<<!";
            mui->textEdit->append(mymsg);
            return  false;

       }


     }

    else
    {
          mainServer->close();

          mui->textEdit->append(QStringLiteral("网络已关闭!"));
          mui->textEdit->moveCursor(QTextCursor::Down);
        // ui->PortButton->setText("Start Listen");
       //  ui->Net_light->setStyleSheet("border-image: url(:/new/icon/picture/gray.png);");
          return  false;
    }


};



bool socket_SYS::server_New_Connect()
{
    waveClient=mainServer->nextPendingConnection();//can not use twice;

           if(!waveClient)
           {
               QDateTime time = QDateTime::currentDateTime();
               QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"声学网络连接失败!";
               mui->textEdit->append(mymsg);
               mui->textEdit->moveCursor(QTextCursor::Down);
               //qDebug()<<waveClient;
               return false;
           }
           else
           {
               QDateTime time = QDateTime::currentDateTime();
               QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"声学网络连接成功!";
               mui->textEdit->append(mymsg);
               mui->textEdit->moveCursor(QTextCursor::Down);
            //   qDebug()<<waveClient->peerAddress();
            //   qDebug()<<waveClient->peerPort();
               connect(waveClient, SIGNAL(readyRead()), this, SLOT(wave_socket_Read_Data()));
               connect(waveClient, SIGNAL(disconnected()), this, SLOT(wave_socket_Disconnected()));
               return true;

           }






}
//int readcount=0;
void socket_SYS::wave_socket_Read_Data()
{
//           if(readcount>=20)
//           {
//               mui->textEdit->clear();
//           }

    QByteArray waveData = waveClient->readAll();
    //Sleep(20);
    char *myData = waveData.data();
    QString str;
    QString myHead;

    str = QString::fromLocal8Bit(myData);


   // qDebug()<<"str==========="<<str;

    if(needLog())
    {
        emit sendMSG2Log(str);
    }

    if(str.size()>=8)
    {
         myHead=str.left(8);
    }

    if(myHead=="YES@@@@@")
    {


        configMSG.append(QString::number( str.split(" ")[1].toInt(nullptr, 16)));
        configMSG.append(QString::number( float(str.split(" ")[2].toInt(nullptr, 16))*0.1));
        configMSG.append(QString::number( str.split(" ")[3].toInt(nullptr, 16)));
        configMSG.append(QString::number( float(str.split(" ")[4].toInt(nullptr, 16))*0.1));
        if(str.split(" ")[5].toInt(nullptr, 16)==1)
        {
            configMSG.append("高斯波");
        }
        else
        {
            configMSG.append("正弦波");
        }
        configMSG.append(QString::number( str.split(" ")[6].toInt(nullptr, 16)));
        configMSG.append(QString::number( str.split(" ")[7].toInt(nullptr, 16)));
        configMSG.append(QString::number( str.split(" ")[8].toInt(nullptr, 16)));

        if(str.split(" ")[9].toInt(nullptr, 16)==1)
        {
            configMSG.append("5MHz");
        }
        else if(str.split(" ")[9].toInt(nullptr, 16)==2)
        {
            configMSG.append("10MHz");
        }
        else if(str.split(" ")[9].toInt(nullptr, 16)==3)
        {
            configMSG.append("15MHz");
        }
        else if(str.split(" ")[9].toInt(nullptr, 16)==4)
        {
            configMSG.append("20MHz");
        }

        configMSG.append(QString::number( str.split(" ")[10].toInt(nullptr, 16)));
        configMSG.append(QString::number( str.split(" ")[11].toInt(nullptr, 16)));
        configMSG.append(QString::number( str.split(" ")[12].toInt(nullptr, 16)));
       //  qDebug()<<"gf"<<str.split(" ")[13].toInt(nullptr, 16);
        if(str.split(" ")[13].toInt(nullptr, 16)==1)
        {
            configMSG.append("开");
        }
        else
        {
            configMSG.append("关");
        }
        int receiveType=str.split(" ")[14].toInt(nullptr, 16);

           switch (receiveType) {
           case 0:
                configMSG.append("1/8");
               break;
           case 1:
                configMSG.append("1/4");
               break;
           case 2:
                configMSG.append("3/8");
               break;
           case 3:
                configMSG.append("1/2");
               break;
           case 4:
                configMSG.append("5/8");
               break;
           case 5:
                configMSG.append("3/4");
               break;
           case 6:
                configMSG.append("7/8");
               break;
           case 7:
                configMSG.append("1");
               break;
           default:
               break;
           }
        emit sendConfig2M(configMSG);
        configMSG.clear();
       // qDebug()<<"str.split("")[4].toDouble()===="<<  QString::number( float(str.split(" ")[2].toInt(nullptr, 16))*0.1) ;
    }

    if(str=="YES")
    {
        emit sendCallBack();

        if(isSendpushed)
        {

            isSendpushed=false;
            emit sendUIlock(true);
        }

    }

    if(noMode)
    {
        QString strHead;
        if(str.size()>=5)
        {
        strHead=str.left(5);
        if(strHead=="$$$$$")
        {
           QDateTime time = QDateTime::currentDateTime();
           QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"开始接收实时波形数据!";
           mui->textEdit->append(mymsg);
           mui->textEdit->moveCursor(QTextCursor::Down);
           mui->textEdit->update();

           QList<QString>cuthead =str.split("*");

           Range=cuthead[0];
           isCurrentData=true;
           noMode=false;
           currentdataStream+=cuthead[1];
           // str.remove(str.indexOf("/r/n"),str.length()-1);
           fileKeyMSG.clear();
           fileKeyMSG=cuthead[0].split("&")[1];
           //fileKeyMSG.remove(0,10);

        }
        else if (strHead=="#####")
        {
            QDateTime time = QDateTime::currentDateTime();
            QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"开始接收波形文件!";
            mui->textEdit->append(mymsg);
            mui->textEdit->moveCursor(QTextCursor::Down);
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
    }
    else
    {
         QString strTips;


        if(isCurrentData)
        {
            QString strHead;
            if(str.size()>=5)
            {
               strHead=str.left(5);
            }
            if(!(strHead=="$$$$$"))
            {
               // qDebug()<<"strTips===="<<strTips;
               // qDebug()<<" currentdataStream+=str===="<<str;
                currentdataStream+=str;

                if(str.size()>=7)
                {
                 strTips=str.right(7);

                if(strTips=="&&&&&\r\n")// 实际使用

                {
                    emit sendUIlock(false);
                    isCurrentData=false;
                    noMode=true;
                    QDateTime time = QDateTime::currentDateTime();
                    QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"实时波形接收结束!";
                    mui->textEdit->append(mymsg);
                    mui->textEdit->moveCursor(QTextCursor::Down);
                    mui->textEdit->update();
                    QString finalcurrentdataStream=currentdataStream.remove(currentdataStream.length()-7,7);//本地测试是9，实际需要改成7
                    //qDebug()<<" finalcurrentdataStream===="<<finalcurrentdataStream;
                    //currentdataStream.remove(0, currentdataStream.indexOf("K")+1);
                    //QString finalcurrentdataStream=currentdataStream;//本地测试是9，实际需要改成7;
                    secondSavemyData.clear();
                    analyzeCurrentData(finalcurrentdataStream,Range);
                    //saveFileData(finalcurrentdataStream);
                    currentdataStream.clear();


                }
              }
            }

        }

    }


   // readcount+=1;


}
void socket_SYS::wave_socket_Disconnected()
{
    QDateTime time = QDateTime::currentDateTime();
    QString mymsg =time.toString("yyyy-MM-dd hh:mm:ss  ")+"声学网络已断开!";
     mui->textEdit->append(mymsg);
     mui->textEdit->moveCursor(QTextCursor::Down);
}

QByteArray socket_SYS::readUIParameter(int type)
{
    QByteArray UIParameter;
    UIParameter.resize(16);
     UIParameter[0]=mui->emissionN->currentIndex()+1;
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
     UIParameter[12]=mui->powercomboBox->currentIndex()+1;
     UIParameter[13]=mui->comboBox->currentIndex();
     UIParameter[14]=1;
     UIParameter[15]=type;
    // UIParameter.resize(sizeof(UIParameterF));
    // memcpy(UIParameter.data(), &UIParameterF, sizeof(UIParameter));
     return UIParameter;

};

void socket_SYS::readMyConfig()
{
    QByteArray ORG;
    ORG.resize(2);
    ORG[0]=1;
    ORG[1]=5;
    uint16_t C3=CRC->ModbusCRC16(ORG);
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(ORG);
    waveClient->write(MSG);
  //  qDebug()<<MSG.toHex();

};
void socket_SYS::wave_socket_SendMSG()
{

    uint16_t C3=CRC->ModbusCRC16(readUIParameter(4));
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(readUIParameter(4));
  //  qDebug()<<"MSG.toHex()"<<MSG.toHex();
    waveClient->write(MSG);

};

void socket_SYS::receiveUIlock()
{
    //isSendpushed=true;
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
    isSendpushed=true;


}

void socket_SYS::receiveFilePath(QString filePath)
{
    myFilePath = filePath;
}

void socket_SYS::analyzeCurrentData(QString cd,QString head)
{
    QList<double>channal_1;
    QList<double>channal_2;
    QString myData;

    QList<QString>cdList=cd.split("\r");
    QList<QString>myRange=head.split("&");
   // qDebug()<<"cd=============="<<cd;
    //qDebug()<<"myRange=============="<<myRange;
    bool ok;
    int countN=cdList.size();



     for(int i=0;i<countN-1;i++)
     {
        if(cdList[i].split(" ").length()>=2)
          {
//              QMessageBox msgBox;
//              msgBox.setText("接收或参考波形数据缺失！");
//              msgBox.exec();
            channal_1.append((cdList[i].split(" ")[0].toDouble(&ok)*1.65)/8192);
            channal_2.append((cdList[i].split(" ")[1].toDouble(&ok)*1.65)/8192);
          }
       //   else
        //  {

        //  }

     }

     emit sendData2Chart(channal_1,channal_2,myRange);

     myData.append( fileKeyMSG+="\r\n");

     for(int i=0;i<countN-1;i++)
     {
          if(cdList[i].split(" ").length()>=2)
          {
        myData.append(QString::number((cdList[i].split(" ")[0].toDouble(&ok)*1.65)/8192,'f', 4) );
        myData.append(" ");
        myData.append(QString::number((cdList[i].split(" ")[1].toDouble(&ok)*1.65)/8192,'f', 4) );
        myData.append("\n");
          }
     }

     emit sendData2Save(myData,myFilePath);
     secondSavemyData=myData;
    //saveFileData(myData);
    //qDebug()<<"channal_1=========="<<channal_1;
    //qDebug()<<"channal_2=========="<<channal_2;
}


bool socket_SYS::needLog()
{

    return needLogFlag;
}
void socket_SYS::receivedNeedLogFlag(bool TOF)
{
     needLogFlag=TOF;
}
 void socket_SYS::shutDownFLag()
 {
     needLogFlag=false;
 };
void socket_SYS::saveFileData(QString fd)
{

        QDateTime time = QDateTime::currentDateTime();
        QString myTime =time.toString("yyyy-MM-dd_hh_mm_ss");
        QFile file(myFilePath+"/"+myTime+".txt");
        if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
        {
          // qDebug()<<"save faile";
        }
        else
        {
          //  qDebug()<<"save ok";
            QTextStream stream(&file);
          //  stream.setEncoding (QStringConverter::System);   //输出编码设为System
            stream<<fd;
            file.close();
        }




};
 void socket_SYS::savecurrentFileData(QString filename,QString filepath)
 {
     QFile file(filepath+"/"+filename+".txt");
     if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
     {
       // qDebug()<<"save faile";
     }
     else
     {
        // qDebug()<<"save ok";
         QTextStream stream(&file);
       //  stream.setEncoding (QStringConverter::System);   //输出编码设为System
         stream<<secondSavemyData;
         file.close();
     }


 };
void socket_SYS::closeMySocket()
{
    waveClient->close();
    mainServer->close();
};


void socket_SYS::receivedMutlOrder(QList<QList<int>> myList)
{




    int orderCount=myList.count();

    QByteArray ORG;

    ORG.resize((orderCount*14));
  //  qDebug()<<"ORG.count()"<<ORG.length();
    for(int i=0;i<orderCount;i++)
    {
        for(int j=0;j<14;j++)
        {

          ORG[i*14+j]=myList.at(i).at(j);
         // qDebug()<<"ORG==N"<<i*12+j;
         // qDebug()<<"current==N"<<myList.at(i).at(j);
        }

    }
    ORG.append(orderCount);
    ORG.append(0x04);
   // qDebug()<<"ORG.count()"<<ORG.length();
    uint16_t C3=CRC->ModbusCRC16(ORG);
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(ORG);
    waveClient->write(MSG);
    isXLcode=true;

};

void socket_SYS::on_pushButton_clicked()
{

}
void socket_SYS::closeSoundPower()
{
    QByteArray ORG;
    ORG.resize(2);
    ORG[0]=0x02;
    ORG[1]=0x07;
    uint16_t C3=CRC->ModbusCRC16(ORG);
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(ORG);
    waveClient->write(MSG);
};
void socket_SYS::openSoundPower()
{
    QByteArray ORG;
    ORG.resize(2);
    ORG[0]=0x01;
    ORG[1]=0x07;
    uint16_t C3=CRC->ModbusCRC16(ORG);
    QByteArray MSG;
    MSG.resize(2);
    MSG[1]=C3>>8;//高位在后
    MSG[0]=(C3<<8)>>8;
    MSG.append(ORG);
    waveClient->write(MSG);
};













