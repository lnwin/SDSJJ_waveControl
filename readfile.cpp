#include "readfile.h"
#include "ui_readfile.h"

readfile::readfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readfile)
{
    ui->setupUi(this);





       ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

       ui->plot->xAxis->setRange(-100, 100);
       ui->plot->yAxis->setRange(-100, 100);
       ui->plot->axisRect()->setupFullAxesBox();
       ui->plot->plotLayout()->insertRow(0);

       QCPTextElement *title = new QCPTextElement(ui->plot, "参考波形", QFont("sans", 10, QFont::Bold));
        ui->plot->plotLayout()->addElement(0, 0, title);
        ui->plot->xAxis->setLabel("数据个数");
        ui->plot->yAxis->setLabel("电压");
        ui->plot->legend->setVisible(true);

        QFont legendFont("Times", 10, QFont::Bold);
        legendFont.setPointSize(10);
        ui->plot->legend->setFont(legendFont);
        ui->plot->legend->setSelectedFont(legendFont);
        ui->plot->legend->setSelectableParts(QCPLegend::spItems);
        ui->plot->addGraph();
        ui->plot->graph()->setName("波形图");
        QPen graphPen;
        graphPen.setColor(QColor(16,177,171));
        graphPen.setWidthF(2);
        ui->plot->graph()->setPen(graphPen);
       // Chart_Mupdata(ui);
        ui->plot->rescaleAxes();
        //=====================================================================================
       ui->plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

       ui->plot_2->xAxis->setRange(-100, 100);
       ui->plot_2->yAxis->setRange(-100, 100);
       ui->plot_2->axisRect()->setupFullAxesBox();
       ui->plot_2->plotLayout()->insertRow(0);

       QCPTextElement *title1 = new QCPTextElement(ui->plot_2, "输出波形", QFont("sans", 10, QFont::Bold));
        ui->plot_2->plotLayout()->addElement(0, 0, title1);
        ui->plot_2->xAxis->setLabel("数据个数");
        ui->plot_2->yAxis->setLabel("电压");
        ui->plot_2->legend->setVisible(true);

        QFont legendFont1("Times", 10, QFont::Bold);
        legendFont1.setPointSize(10);
        ui->plot_2->legend->setFont(legendFont1);
        ui->plot_2->legend->setSelectedFont(legendFont1);
        ui->plot_2->legend->setSelectableParts(QCPLegend::spItems);
        ui->plot_2->addGraph();
        ui->plot_2->graph()->setName("波形图");
        QPen graphPen1;
        graphPen1.setColor(QColor(160,20,200));
        graphPen1.setWidthF(2);
        ui->plot_2->graph()->setPen(graphPen1);
       // Chart_Mupdata(ui);
        ui->plot_2->rescaleAxes();


}

readfile::~readfile()
{
    delete ui;
}
bool readfile::readMyfile(QString filename)
{

    QFile file(filename);
    bool isfirst=true;
    int startN,endN;
    QList<QString> l1;
    l1.resize(10);
    QList<QString> l2;
    QList<QString> l3;
    QVector<double> myX(10);
    QVector<double> myY(10);
    QVector<double> myY2(10);
    int datacount=0;
    // 一行一行的读

    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
    {
        QMessageBox::about(NULL, "文件", "文件打开失败");
    }
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();

        if(!line.isEmpty())
        {
           // qDebug()<<"readLine==="<<line;
            if(isfirst)
            {
                ui->textEdit->clear();
                ui->textEdit->append(line);
                qDebug()<<line;
                l1= line.split("：");
                qDebug()<<"l1==="<<l1;
                l2=l1[6].split("K");
                l3=l1[7].split("K");
                startN= l2[0].toInt();
                endN= l3[0].toInt();
                myX.resize(endN*1000);
                myY.resize(endN*1000);
                myY2.resize(endN*1000);
                isfirst=false;
            }
            else
            {
                //qDebug()<<line;
                myX.push_back(datacount);
                //qDebug()<<line.split(" ");
                myY.push_back(line.split(" ")[0].toFloat());
                myY2.push_back(line.split(" ")[1].toFloat());
                datacount+=1;

            }

        }

    }

    ui->plot->graph()->setData(myX,myY);
    ui->plot->graph()->setName( QString::number(startN,10)+"k--"+QString::number(endN,10)+ "k波形图");
    ui->plot->xAxis->rescale();
    // 自适应y轴范围
    ui->plot->yAxis->rescale();
    ui->plot_2->graph()->setData(myX,myY2);
    ui->plot_2->graph()->setName( QString::number(startN,10)+"k--"+QString::number(endN,10)+ "k波形图");
    ui->plot_2->xAxis->rescale();
    // 自适应y轴范围
    ui->plot_2->yAxis->rescale();
    ui->plot_2->replot();
    ui->plot->replot();
    file.close();
    isfirst=true;
    return true;

};




void readfile::on_pushButton_clicked()
{
    this->hide();
}

