#ifndef MYCHART_H
#define MYCHART_H

#include <QObject>
#include <ui_mainwindow.h>
#include <QThread>
class myChart:public QThread
{
    Q_OBJECT
public:
    myChart(Ui::MainWindow *ui);

    Ui::MainWindow *mcui;
private slots:

};

#endif // MYCHART_H
