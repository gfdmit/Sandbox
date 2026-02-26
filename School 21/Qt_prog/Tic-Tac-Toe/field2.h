#ifndef FIELD2_H
#define FIELD2_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class Field2;
}

class Field2 : public QWidget
{
    Q_OBJECT

public:
    Field2(QWidget *parent = nullptr);
    ~Field2();

private slots:
    bool isRowWin(int i);
    bool isColWin(int i);
    bool isDiagWin(int i);
    int isWin();
    void reset();
    void finalWidget(int i);
    void bot();

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
    Ui::Field2 *ui;
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

#endif // FIELD2_H
