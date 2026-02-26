#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QLineEdit>
#include <qradiobutton.h>


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

    int w_clickedTimes;

signals:
    void firstWindow();

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_Dobavit_Button_clicked();
    void on_Izmenit_Button_clicked();
    void on_Udalit_Button_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void filt();
    void reset();



private:
    Ui::Form *ui;
    QSqlDatabase datab;
    QSqlQuery *query;
    QSqlTableModel *model;
    QLineEdit *textBox;

    QRadioButton* first;
    QRadioButton* second;
    QRadioButton* third;
    QRadioButton* fouth;
    int row;
};

#endif // FORM_H
