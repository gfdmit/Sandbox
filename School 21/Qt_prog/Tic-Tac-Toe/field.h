#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Field;
}

class Field : public QWidget
{
    Q_OBJECT

public:
    Field(QWidget *parent = nullptr);
    ~Field();

private slots:
    int isWin();
    void reset();
    void finalWidget(int i);

    void on_pushButton1_1_clicked();

    void on_pushButton1_2_clicked();

    void on_pushButton1_3_clicked();

    void on_pushButton2_1_clicked();

    void on_pushButton2_2_clicked();

    void on_pushButton2_3_clicked();

    void on_pushButton3_1_clicked();

    void on_pushButton3_2_clicked();

    void on_pushButton3_3_clicked();

private:
    Ui::Field *ui;
    QPushButton button1_1;
    QPushButton button1_2;
    QPushButton button1_3;
    QPushButton button2_1;
    QPushButton button2_2;
    QPushButton button2_3;
    QPushButton button3_1;
    QPushButton button3_2;
    QPushButton button3_3;
};

#endif // FIELD_H
