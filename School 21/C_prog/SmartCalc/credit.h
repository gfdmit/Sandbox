#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

namespace Ui {
class Credit;
}

class Credit : public QMainWindow
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private slots:
    void on_action1_triggered();

    void on_action2_triggered();

    void on_action3_triggered();

    void on_action4_triggered();

private:
    Ui::Credit *ui;
};

#endif // CREDIT_H
