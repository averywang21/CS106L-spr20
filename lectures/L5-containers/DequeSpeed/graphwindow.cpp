
#include "graphwindow.h"
#include "ui_windowform.h"
#include <iostream>
#include <string>

using std::string;

GraphWindow::GraphWindow(QWidget *parent) : QMainWindow {parent}, ui{new Ui::Form}{
    srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);
    ui->customPlot->xAxis->setLabel("x Axis");
    ui->customPlot->yAxis->setLabel("y Axis");
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);

}
void GraphWindow::setTitle(const string& graph_title) {
    ui->customPlot->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(ui->customPlot, graph_title.c_str(), QFont("sans", 17, QFont::Bold));
    ui->customPlot->plotLayout()->addElement(0, 0, title);
}

GraphWindow::~GraphWindow() {
    delete ui;
}

void GraphWindow::addGraph(const string& name, const string &color, const std::vector<double>& x, const std::vector<double>& y) {

    // create graph and assign data to it:
    const QVector<double> x_q, y_q;

    ui->customPlot->addGraph();

    ui->customPlot->graph()->setName(name.c_str());
    ui->customPlot->graph()->setData(x_q.fromStdVector(x), y_q.fromStdVector(y));

    QPen graphPen;
    graphPen.setColor(QColor(color.c_str()));//rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setWidth(3);
    ui->customPlot->graph()->setPen(graphPen);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}


void GraphWindow::setXAxisRange(double start, double end) {
    ui->customPlot->xAxis->setRange(start, end);
}

void GraphWindow::setYAxisRange(double start, double end) {
    ui->customPlot->yAxis->setRange(start, end);
}



