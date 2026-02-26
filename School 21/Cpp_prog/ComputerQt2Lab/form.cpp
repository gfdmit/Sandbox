#include "form.h"
#include "ui_form.h"
#include <QApplication>
#include <QtWidgets>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    datab = QSqlDatabase::addDatabase("QSQLITE");
    datab.setDatabaseName("./myDataBase.datab");
    if(datab.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not");
    }
    query = new QSqlQuery(datab);
    query->exec("CREATE TABLE Computer(Название TEXT, Производитель TEXT, Цена INT, Дата покупки DATE);");

    model = new QSqlTableModel(this,datab);
    model->setTable("Computer");
    model->select();

    ui->tableView->setModel(model);
}

Form::~Form()
{
    delete ui;
}



void Form::on_Dobavit_Button_clicked()
{
    model->insertRow(model->rowCount());
}


void Form::on_Udalit_Button_clicked()
{
    model->removeRow(row);
}


void Form::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void Form::on_Izmenit_Button_clicked()
{
    this->close();
    emit firstWindow();
}


void Form::on_pushButton_clicked()
{

    QApplication app();

    first = new QRadioButton("&Название");
    second = new QRadioButton("&Производитель");
    third = new QRadioButton("&Цена");
    fouth = new QRadioButton("Дата покупки");

    QGroupBox *gbx = new QGroupBox("&Выберите фильтр");

    QPushButton* one = new QPushButton("&Отфильтровать");
    QObject::connect(one,SIGNAL(clicked()),this,SLOT(filt()));
    QPushButton* reset = new QPushButton("&Сбросить");
    QObject::connect(reset,SIGNAL(clicked()),this,SLOT(reset()));

    textBox = new QLineEdit();

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(first);
    pvbxLayout->addWidget(second);
    pvbxLayout->addWidget(third);
    pvbxLayout->addWidget(fouth);
    pvbxLayout->addWidget(textBox);
    pvbxLayout->addWidget(one);
    pvbxLayout->addWidget(reset);
    gbx->setLayout(pvbxLayout);
    gbx->resize(250,250);
    gbx->show();
}

void Form::filt()
{
    QString pattern = "";
    QString filter = textBox->text();
    if (first->isChecked())
        pattern += "Название =\'";
    else if (second->isChecked())
        pattern += "Производитель =\'";
    else if (third->isChecked())
        pattern += "Цена =\'";
    else if (fouth->isChecked())
        pattern += "Дата покупки =\'";
    pattern += filter;
    pattern += "\'";
    model->setFilter(pattern);
    model->select();
}

void Form::reset()
{
    datab = QSqlDatabase::addDatabase("QSQLITE");
    datab.setDatabaseName("./myDataBase.datab");
    if(datab.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not");
    }
    query = new QSqlQuery(datab);
    query->exec("CREATE TABLE Computer(Название TEXT, Производитель TEXT, Цена INT, Дата покупки DATE);");

    model = new QSqlTableModel(this,datab);
    model->setTable("Computer");
    model->select();

    ui->tableView->setModel(model);
}
