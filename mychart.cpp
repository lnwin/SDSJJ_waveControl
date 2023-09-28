#include "mychart.h"

myChart::myChart()
{

}

void myChart::chart_Init(Ui::MainWindow *ui)
{
       mcui=ui;
       mcui->channel1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

       mcui->channel1->xAxis->setRange(-100, 100);
       mcui->channel1->yAxis->setRange(-100, 100);
       mcui->channel1->axisRect()->setupFullAxesBox();
       mcui->channel1->plotLayout()->insertRow(0);

       QCPTextElement *title = new QCPTextElement(mcui->channel1, "参考波形", QFont("sans", 10, QFont::Bold));
        mcui->channel1->plotLayout()->addElement(0, 0, title);
        mcui->channel1->xAxis->setLabel("数据个数");
        mcui->channel1->yAxis->setLabel("电压");
        mcui->channel1->legend->setVisible(true);

        QFont legendFont("Times", 10, QFont::Bold);
        legendFont.setPointSize(10);
        mcui->channel1->legend->setFont(legendFont);
        mcui->channel1->legend->setSelectedFont(legendFont);
        mcui->channel1->legend->setSelectableParts(QCPLegend::spItems);
        mcui->channel1->addGraph();
        mcui->channel1->graph()->setName("波形图");
        QPen graphPen;
        graphPen.setColor(QColor(16,177,171));
        graphPen.setWidthF(2);
         mcui->channel1->graph()->setPen(graphPen);
       // Chart_Mupdata(ui);
         mcui->channel1->rescaleAxes();
       //=====================================================================================================================
         mcui->channel2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);

         mcui->channel2->xAxis->setRange(-100, 100);
         mcui->channel2->yAxis->setRange(-100, 100);
         mcui->channel2->axisRect()->setupFullAxesBox();
         mcui->channel2->plotLayout()->insertRow(0);

         QCPTextElement *title1 = new QCPTextElement(mcui->channel2, "输出波形", QFont("sans", 10, QFont::Bold));
          mcui->channel2->plotLayout()->addElement(0, 0, title1);
         mcui->channel2->xAxis->setLabel("数据个数");
          mcui->channel2->yAxis->setLabel("电压");
          mcui->channel2->legend->setVisible(true);

          QFont legendFont2("Times", 10, QFont::Bold);
          legendFont2.setPointSize(10);
          mcui->channel2->legend->setFont(legendFont2);
          mcui->channel2->legend->setSelectedFont(legendFont2);
          mcui->channel2->legend->setSelectableParts(QCPLegend::spItems);
          mcui->channel2->addGraph();
          mcui->channel2->graph()->setName("波形图");
          QPen graphPen2;
          graphPen2.setColor(QColor(160,20,200));
          graphPen2.setWidthF(2);
           mcui->channel2->graph()->setPen(graphPen2);
         // Chart_Mupdata(ui);
           mcui->channel2->rescaleAxes();



}
void myChart::chartUpdate(QList<double>C1,QList<double>C2,QList<QString>range)
{

if((!C1.empty())&&(!C2.empty()))
{
    bool YYY;
    int dataLength=C1.size();
    double C1max = *std::max_element(std::begin(C1), std::end(C1));
    double C1min = *std::min_element(std::begin(C1), std::end(C1));
    double C2max = *std::max_element(std::begin(C2), std::end(C2));
    double C2min = *std::min_element(std::begin(C2), std::end(C2));
    int xStart=(range[0].split("|")[1].toInt(&YYY));
    int xEnd=(range[0].split("|")[2].toInt(&YYY));//本地是4，实际是2
//    qDebug()<<"dataLength"<<dataLength;
//    qDebug()<<"range"<<range;
//    qDebug()<<"xStart"<<xStart;
//    qDebug()<<"xEnd"<<xEnd;
//    qDebug()<<"C2max"<<C2max;
//    qDebug()<<"C2min"<<C2min;

    mcui->channel1->yAxis->setRange(C1min*1.1, C1max*1.1);
    mcui->channel1->xAxis->setRange(0, dataLength);
    mcui->channel2->yAxis->setRange(C2min*1.1, C2max*1.1);
    mcui->channel2->xAxis->setRange(0, dataLength);
    QVector<double> myX(dataLength);
    QVector<double> myC1Y(dataLength);
    QVector<double> myC2Y(dataLength);
   for(int i=0;i<dataLength;i++)
   {
       myX[i]=i;
       myC1Y[i]=C1[i];
       myC2Y[i]=C2[i];
   }

  // qDebug()<<"D0==="<< myC1Y[0];
  // qDebug()<<"D1==="<< myC2Y[0];

   mcui->channel1->graph()->setData(myX,myC1Y);
   mcui->channel1->graph()->setName( QString::number(xStart,10)+"k--"+QString::number(xEnd,10)+ "k波形图");
   mcui->channel1->replot();
   mcui->channel2->graph()->setData(myX,myC2Y);
   mcui->channel2->graph()->setName( QString::number(xStart,10)+"k--"+QString::number(xEnd,10)+ "k波形图");
   mcui->channel2->replot();

}




};





void myChart::on_pushButton_clicked()
{

}



