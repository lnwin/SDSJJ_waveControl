#include "savethread.h"
#include <QDateTime>
#include <QFile>
savethread::savethread()
{

}

void savethread::savemydate(QString date,QString filepath)
{
    QDateTime time = QDateTime::currentDateTime();

    QString myHz = date.split("\r\n")[0].split("发射频率")[1].split("|")[0].remove(0,1);
    QString myTime =time.toString("yyyy-MM-dd_hh_mm_ss")+"_"+myHz;
    QFile file(filepath+"/"+myTime+".txt");
    if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        // qDebug()<<"save faile";
    }
    else
    {
        //  qDebug()<<"save ok";
        QTextStream stream(&file);
        //  stream.setEncoding (QStringConverter::System);   //输出编码设为System
        stream<<date;
        file.close();
    }

}
