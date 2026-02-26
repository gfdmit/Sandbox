#include "credit.h"
#include "ui_credit.h"
#include "externs.h"

Credit::Credit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_action1_triggered()
{
    w->show();
    this->close();
}


void Credit::on_action2_triggered()
{
    engine->show();
    this->close();
}


void Credit::on_action3_triggered()
{
    graphic->show();
    this->close();
}


void Credit::on_action4_triggered()
{
}

