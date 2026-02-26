//#include "parser.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"
#include "externs.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void::MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();

    QString new_label;
    new_label = ui->result_show->text() + button->text();

    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButtonPercent_clicked() {
    ui->result_show->setText(ui->result_show->text() + "mod");
}


void MainWindow::on_pushButtonSqrt_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "sqrt(");
}


void MainWindow::on_pushButtonMult_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "*");
}


void MainWindow::on_pushButtonMinus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "-");
}


void MainWindow::on_pushButtonPlus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "+");
}


void MainWindow::on_pushButtonSub_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "/");
}


void MainWindow::on_pushButtonC_clicked()
{
    ui->result_show->setText("");
}


void MainWindow::on_pushButtonCE_clicked()
{
    ui->result_show->setText("");
}


void MainWindow::on_pushButtonPow_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "^2");
}


void MainWindow::on_pushButtonRevers_clicked()
{
    ui->result_show->setText("1/(" + ui->result_show->text() + ")");
}


void MainWindow::on_pushButtonDel_clicked()
{
    if (ui->result_show->text().length() != 0) {
        ui->result_show->setText(ui->result_show->text().chopped(1));
    }
}


void MainWindow::on_pushButtonDot_clicked()
{
    ui->result_show->setText(ui->result_show->text() + ".");
}


void MainWindow::on_pushButtonResult_clicked()
{
    std::string str = ui->result_show->text().toStdString();
    char *c_str = const_cast<char *>(str.c_str());
    double num = parser(c_str);
    QString output = QString::number(num);
    ui->result_show->setText(output);

}


void MainWindow::on_pushButtonUnary_clicked()
{
    ui->result_show->setText("-(" + ui->result_show->text() + ")");
}


void MainWindow::on_action_2_triggered()
{
}


void MainWindow::on_action_3_triggered()
{
    engine->show();
    this->close();
}


void MainWindow::on_action_4_triggered()
{
    graphic->show();
    this->close();
}


void MainWindow::on_action_5_triggered()
{
    credit->show();
    this->close();
}

