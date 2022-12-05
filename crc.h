#ifndef CRC_H
#define CRC_H

#include <QObject>

class crc : public QObject
{
    Q_OBJECT
public:
    explicit crc(QObject *parent = nullptr);    
    uint16_t ModbusCRC16(QByteArray senddata);
signals:

};

#endif // CRC_H
