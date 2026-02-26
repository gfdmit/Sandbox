#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include <QMouseEvent>

QWidget *par;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 600);
    par = parent;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonTwoPlayer_clicked()
{
    fieldPlayer.show();
}


void MainWindow::on_buttonOnePlayer_clicked()
{
    fieldBot.show();
}

