//#include "parser.h"
#include "engine.h"
#include "ui_engine.h"
#include "externs.h"
#include <string>


Engine::Engine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Engine)
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

Engine::~Engine()
{
    delete ui;
}

void::Engine::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();

    QString new_label;
    new_label = ui->result_show->text() + button->text();

    ui->result_show->setText(new_label);
}

void Engine::on_action1_triggered()
{
    w->show();
    this->close();
}


void Engine::on_action2_triggered()
{
}


void Engine::on_action3_triggered()
{
    graphic->show();
    this->close();
}


void Engine::on_action4_triggered()
{
    credit->show();
    this->close();
}


void Engine::on_pushButtonLn_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "ln(");
}


void Engine::on_pushButtonUnary_clicked()
{
    ui->result_show->setText("-(" + ui->result_show->text() + ")");
}


void Engine::on_pushButtonDot_clicked()
{
    ui->result_show->setText(ui->result_show->text() + ".");
}


void Engine::on_pushButtonResult_clicked()
{
    std::string str = ui->result_show->text().toStdString();
    char *c_str = const_cast<char *>(str.c_str());
    double num = parser(c_str);
    QString output = QString::number(num);
    ui->result_show->setText(output);
}


void Engine::on_pushButtonPlus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "+");
}


void Engine::on_pushButtonLog_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "log");
}


void Engine::on_pushButton10Pow_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "10^");
}


void Engine::on_pushButtonMinus_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "-");
}


void Engine::on_pushButtonMult_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "*");
}


void Engine::on_pushButtonPow_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "^");
}


void Engine::on_pushButtonSub_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "/");
}


void Engine::on_pushButtonMod_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "mod");
}


void Engine::on_pushButtonClose_clicked()
{
    ui->result_show->setText(ui->result_show->text() + ")");
}


void Engine::on_pushButtonOpen_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "(");
}


void Engine::on_pushButtonSqrt_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "sqrt(");
}


void Engine::on_pushButtonCE_clicked()
{
    ui->result_show->setText("");
}


void Engine::on_pushButtonE_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "2.718281");
}


void Engine::on_pushButtonPi_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "3.141592");
}


void Engine::on_pushButtonRevers_clicked()
{
    ui->result_show->setText("1/(" + ui->result_show->text() + ")");
}


void Engine::on_pushButtonPow2_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "^2");
}


void Engine::on_pushButtonDel_clicked()
{
    if (ui->result_show->text().length() != 0) {
        ui->result_show->setText(ui->result_show->text().chopped(1));
    }
}


void Engine::on_pushButtonC_clicked()
{
    ui->result_show->setText("");
}


void Engine::on_pushButtonTan_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "tan(");
}


void Engine::on_pushButtonCos_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "cos(");
}


void Engine::on_pushButtonSin_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "sin(");
}

