
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "credit.h"
#include "engine.h"
#include "graphic.h"

#ifdef __cplusplus
extern "C" {
    double parser(char* str);
}
#endif


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    void digits_numbers();
    void on_pushButtonSqrt_clicked();
    void on_pushButtonPercent_clicked();
    void on_pushButtonMult_clicked();
    void on_pushButtonMinus_clicked();
    void on_pushButtonPlus_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonC_clicked();
    void on_pushButtonCE_clicked();
    void on_pushButtonPow_clicked();
    void on_pushButtonRevers_clicked();
    void on_pushButtonDel_clicked();
    void on_pushButtonDot_clicked();
    void on_pushButtonUnary_clicked();
    void on_pushButtonResult_clicked();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();
};

#endif // MAINWINDOW_H
