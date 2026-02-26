#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "form.h"




QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    int w_clickedTimes;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    Ui::Widget *ui;
    QSqlDatabase datab;
    QSqlQuery *query;
    QSqlTableModel *model;

    Form *editor;

private slots:
    void on_Izmenit_Button_clicked();
    void on_Perec_clicked();
    void on_Update_clicked();
};
#endif // WIDGET_H
