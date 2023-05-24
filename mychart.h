#ifndef MYCHART_H
#define MYCHART_H

#include <QObject>
#include <ui_mainwindow.h>
#include <QThread>
class myChart:public QThread
{
    Q_OBJECT
public:
    myChart();

    Ui::MainWindow *mcui;
public slots:

    void chart_Init(Ui::MainWindow *ui);
    void chartUpdate(QList<double>C1,QList<double>C2,QList<QString>range);


private slots:


};

#endif // MYCHART_H
