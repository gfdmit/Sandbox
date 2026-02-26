
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include "field2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonTwoPlayer_clicked();

    void on_buttonOnePlayer_clicked();

private:
    Ui::MainWindow *ui;
    Field fieldPlayer;
    Field2 fieldBot;
};



#endif // MAINWINDOW_H
