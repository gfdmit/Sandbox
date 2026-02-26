
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QMainWindow>
#include <QVector>

#ifdef __cplusplus
extern "C" {
void graphicParser(char *str, double x1, double x2, double *Yposes);
}
#endif

namespace Ui {
class Graphic;
}

class Graphic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graphic(QWidget *parent = nullptr);
    ~Graphic();

private slots:
    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_buttonGraph_clicked();

private:
    Ui::Graphic *ui;
    double xMin, xMax, yMin, yMax;
    QVector<double> x, y;
};

#endif // GRAPHIC_H
