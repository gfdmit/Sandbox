#ifndef ENGINE_H
#define ENGINE_H

#include <QMainWindow>

namespace Ui {
class Engine;
}

class Engine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Engine(QWidget *parent = nullptr);
    ~Engine();

private slots:
    void digits_numbers();

    void on_action1_triggered();

    void on_action2_triggered();

    void on_action3_triggered();

    void on_action4_triggered();

    void on_pushButtonLn_clicked();

    void on_pushButtonUnary_clicked();

    void on_pushButtonDot_clicked();

    void on_pushButtonResult_clicked();

    void on_pushButtonPlus_clicked();

    void on_pushButtonLog_clicked();

    void on_pushButton10Pow_clicked();

    void on_pushButtonMinus_clicked();

    void on_pushButtonMult_clicked();

    void on_pushButtonPow_clicked();

    void on_pushButtonSub_clicked();

    void on_pushButtonMod_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonOpen_clicked();

    void on_pushButtonSqrt_clicked();

    void on_pushButtonCE_clicked();

    void on_pushButtonE_clicked();

    void on_pushButtonPi_clicked();

    void on_pushButtonRevers_clicked();

    void on_pushButtonPow2_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonC_clicked();

    void on_pushButtonTan_clicked();

    void on_pushButtonCos_clicked();

    void on_pushButtonSin_clicked();

private:
    Ui::Engine *ui;
};

#endif // ENGINE_H
