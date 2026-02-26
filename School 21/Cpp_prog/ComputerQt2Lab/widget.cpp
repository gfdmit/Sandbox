#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QtWidgets>
#include <unistd.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
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
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("Computer");
    model->select();
    ui->tableView->setModel(model);
    editor = new Form();
    connect(editor,&Form::firstWindow,this,&Widget::show);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_Izmenit_Button_clicked()
{
    editor->show();
    this->close();
}

void Widget::on_Perec_clicked()
{
    QLabel *label_2 = new QLabel;
    label_2->resize(867,660);


    QApplication app();
    QGroupBox *zaglushka = new QGroupBox("&Заглушка");

    QRadioButton* first = new QRadioButton("&Бесполезный");
    QRadioButton* second = new QRadioButton("&Виджет");
    QRadioButton* third = new QRadioButton("&Который");
    QRadioButton* fouth = new QRadioButton("Ничего не делает");

    QVBoxLayout* zaglushkaLayout = new QVBoxLayout;
    zaglushkaLayout->addWidget(first);
    zaglushkaLayout->addWidget(second);
    zaglushkaLayout->addWidget(third);
    zaglushkaLayout->addWidget(fouth);
    zaglushka->setLayout(zaglushkaLayout);
    zaglushka->resize(250, 100);

    QWidget *zaglushka2 = new QWidget;
    QLCDNumber* plcd = new QLCDNumber;
    QSpinBox* pspb = new QSpinBox;

    plcd->setSegmentStyle(QLCDNumber::Filled);
    plcd->setMode(QLCDNumber::Dec);

    pspb->setFixedHeight(30);

    QObject::connect(pspb, SIGNAL(valueChanged(int)),plcd,SLOT(display(int)));
    QVBoxLayout* p_lays = new QVBoxLayout;
    p_lays->addWidget(plcd);
    p_lays->addWidget(pspb);
    zaglushka2->setLayout(p_lays);
    zaglushka2->resize(210,170);

    QWidget *widget = new QWidget;
    widget->resize(150,80);
    QPushButton* one = new QPushButton("&Заглушка №1");
    QObject::connect(one,SIGNAL(clicked()),zaglushka,SLOT(show()));
    QPushButton* two = new QPushButton("&Заглушка №2");
    QObject::connect(two,SIGNAL(clicked()),zaglushka2,SLOT(show()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(one);
    layout->addWidget(two);
    widget->setLayout(layout);
    widget->show();
}


void Widget::on_Update_clicked()
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
    query->exec("CREATE TABLE Computer(Название TEXT, Производитель TEXT, Цена INT);");

    model = new QSqlTableModel(this,datab);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("Computer");
    model->select();
    ui->tableView->setModel(model);
    editor = new Form();
    connect(editor,&Form::firstWindow,this,&Widget::show);
}

