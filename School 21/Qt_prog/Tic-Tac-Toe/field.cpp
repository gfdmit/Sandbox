#include "field.h"
#include "ui_field.h"
#include <vector>
#include <QMessageBox>

bool isX = 1;
size_t counter = 0;
std::vector<std::vector<int>> vecField(3, std::vector<int>(3, 0));

Field::Field(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Field)
{
    ui->setupUi(this);
    this->setFixedSize(600,600);
}

Field::~Field()
{
    delete ui;
}

void Field::finalWidget(int i) {
    QMessageBox final;
    if (i == 0)
        final.setText("Draw");
    if (i == 1)
        final.setText("First player win!");
    if (i == 2)
        final.setText("Second player win!");
    final.setInformativeText("Again?");
    final.setStandardButtons(QMessageBox::Yes | QMessageBox::Close);
    int res = final.exec();
    if (res == QMessageBox::Yes) {
        reset();
    } else {
        reset();
        this->close();
    }
}

void Field::reset() {
    isX = 1;
    counter = 0;
    ui->pushButton1_1->setText("");
    ui->pushButton1_2->setText("");
    ui->pushButton1_3->setText("");
    ui->pushButton2_1->setText("");
    ui->pushButton2_2->setText("");
    ui->pushButton2_3->setText("");
    ui->pushButton3_1->setText("");
    ui->pushButton3_2->setText("");
    ui->pushButton3_3->setText("");
    for (size_t i = 0; i != 3; ++i) {
        for (size_t j = 0; j != 3; ++j) {
            vecField[i][j] = 0;
        }
    }
}

bool isRowWin(int i) {
    if (vecField[0][0] == i && vecField[0][1] == i && vecField[0][2] == i) return true;
    if (vecField[1][0] == i && vecField[1][1] == i && vecField[1][2] == i) return true;
    if (vecField[2][0] == i && vecField[2][1] == i && vecField[2][2] == i) return true;
    return false;
}

bool isColWin(int i) {
    if (vecField[0][0] == i && vecField[1][0] == i && vecField[2][0] == i) return true;
    if (vecField[0][1] == i && vecField[1][1] == i && vecField[2][1] == i) return true;
    if (vecField[0][2] == i && vecField[1][2] == i && vecField[2][2] == i) return true;
    return false;
}

bool isDiagWin(int i) {
    if (vecField[0][0] == i && vecField[1][1] == i && vecField[2][2] == i) return true;
    if (vecField[0][2] == i && vecField[1][1] == i && vecField[2][0] == i) return true;
    return false;
}

int Field::isWin() {
    if (isRowWin(1) || isColWin(1) || isDiagWin(1)) finalWidget(1);
    if (isRowWin(2) || isColWin(2) || isDiagWin(2)) finalWidget(2);
    if (counter == 9) finalWidget(0);
    return 0;
}

void Field::on_pushButton1_1_clicked()
{
    if (vecField[0][0] == 0) {
        if (isX) {
            ui->pushButton1_1->setText("x");
            vecField[0][0] = 1;
            isX = false;
        } else {
            ui->pushButton1_1->setText("o");
            vecField[0][0] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton1_2_clicked()
{
    if (vecField[0][1] == 0) {
        if (isX) {
            ui->pushButton1_2->setText("x");
            vecField[0][1] = 1;
            isX = false;
        } else {
            ui->pushButton1_2->setText("o");
            vecField[0][1] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton1_3_clicked()
{
    if (vecField[0][2] == 0) {
        if (isX) {
            ui->pushButton1_3->setText("x");
            vecField[0][2] = 1;
            isX = false;
        } else {
            ui->pushButton1_3->setText("o");
            vecField[0][2] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton2_1_clicked()
{
    if (vecField[1][0] == 0) {
        if (isX) {
            ui->pushButton2_1->setText("x");
            vecField[1][0] = 1;
            isX = false;
        } else {
            ui->pushButton2_1->setText("o");
            vecField[1][0] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton2_2_clicked()
{
    if (vecField[1][1] == 0) {
        if (isX) {
            ui->pushButton2_2->setText("x");
            vecField[1][1] = 1;
            isX = false;
        } else {
            ui->pushButton2_2->setText("o");
            vecField[1][1] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton2_3_clicked()
{
    if (vecField[1][2] == 0) {
        if (isX) {
            ui->pushButton2_3->setText("x");
            vecField[1][2] = 1;
            isX = false;
        } else {
            ui->pushButton2_3->setText("o");
            vecField[1][2] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton3_1_clicked()
{
    if (vecField[2][0] == 0) {
        if (isX) {
            ui->pushButton3_1->setText("x");
            vecField[2][0] = 1;
            isX = false;
        } else {
            ui->pushButton3_1->setText("o");
            vecField[2][0] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton3_2_clicked()
{
    if (vecField[2][1] == 0) {
        if (isX) {
            ui->pushButton3_2->setText("x");
            vecField[2][1] = 1;
            isX = false;
        } else {
            ui->pushButton3_2->setText("o");
            vecField[2][1] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

void Field::on_pushButton3_3_clicked()
{
    if (vecField[2][2] == 0) {
        if (isX) {
            ui->pushButton3_3->setText("x");
            vecField[2][2] = 1;
            isX = false;
        } else {
            ui->pushButton3_3->setText("o");
            vecField[2][2] = 2;
            isX = true;
        }
        counter++;
    }
    isWin();
}

