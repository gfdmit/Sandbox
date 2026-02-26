#include "graphic.h"
#include "ui_graphic.h"
#include "externs.h"

Graphic::Graphic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graphic)
{
    ui->setupUi(this);
}

Graphic::~Graphic()
{
    delete ui;
}

void Graphic::on_action_2_triggered()
{
    w->show();
    this->close();
}

void Graphic::on_action_3_triggered()
{
    engine->show();
    this->close();
}

void Graphic::on_action_4_triggered()
{
}

void Graphic::on_action_5_triggered()
{
    credit->show();
    this->close();
}

void Graphic::on_buttonGraph_clicked()
{
    xMin = ui->xMin->text().toDouble();
    xMax = ui->xMax->text().toDouble();
    yMin = ui->yMin->text().toDouble();
    yMax = ui->yMax->text().toDouble();
    ui->widget->xAxis->setRange(xMin, xMax);
    ui->widget->yAxis->setRange(yMin, yMax);
    double Yposes[201] = {0};
    std::string str = ui->result->text().toStdString();
    char *c_str = const_cast<char *>(str.c_str());
    graphicParser(c_str, xMin, xMax, Yposes);
    double x1 = xMin, x2 = xMax;
    double step = (x2 - x1) / 200;
    for (int counter = 0; x1 <= x2; x1 += step, counter++) {
        x.push_back(x1);
        y.push_back(Yposes[counter]);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

