#ifndef SAVETHREAD_H
#define SAVETHREAD_H

#include <QObject>
#include <QThread>
class savethread:public QThread
{
    Q_OBJECT
public:
    savethread();

public slots:

    void savemydate(QString date,QString filename);
};

#endif // SAVETHREAD_H
