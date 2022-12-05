#include "crc.h"

crc::crc(QObject *parent) : QObject(parent)
{

}

uint16_t crc::ModbusCRC16(QByteArray senddata)
{
    int len=senddata.size();
        uint16_t wcrc=0XFFFF;//预置16位crc寄存器，初值全部为1
        uint8_t temp;//定义中间变量
        int i=0,j=0;//定义计数
        for(i=0;i<len;i++)//循环计算每个数据
        {
           temp=senddata.at(i);
           wcrc^=temp;
           for(j=0;j<8;j++){
              //判断右移出的是不是1，如果是1则与多项式进行异或。
              if(wcrc&0X0001){
                  wcrc>>=1;//先将数据右移一位
                  wcrc^=0XA001;//与上面的多项式进行异或
              }
              else//如果不是1，则直接移出
                  wcrc>>=1;//直接移出
           }
        }
        temp=wcrc;//crc的值
        return wcrc;
}
