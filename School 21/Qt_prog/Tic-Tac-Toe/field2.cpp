#include "field2.h"
#include "ui_field2.h"
#include <vector>
#include <QMessageBox>
#include <cstdlib>
#include <string>

size_t counterBot = 0;
std::vector<QPushButton*> vecFieldBut(9);
std::vector<std::vector<int>> vecFieldBot(3, std::vector<int>(3, 0));

Field2::Field2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Field2)
{
    ui->setupUi(this);
    this->setFixedSize(600, 600);
    vecFieldBut[0] = (ui->pushButton1_1);
    vecFieldBut[1] = (ui->pushButton1_2);
    vecFieldBut[2] = (ui->pushButton1_3);
    vecFieldBut[3] = (ui->pushButton2_1);
    vecFieldBut[4] = (ui->pushButton2_2);
    vecFieldBut[5] = (ui->pushButton2_3);
    vecFieldBut[6] = (ui->pushButton3_1);
    vecFieldBut[7] = (ui->pushButton3_2);
    vecFieldBut[8] = (ui->pushButton3_3);
}

Field2::~Field2()
{
    delete ui;
}

void Field2::finalWidget(int i) {
    QMessageBox final;
    if (i == 0)
        final.setText("Draw");
    if (i == 1)
        final.setText("Player win!");
    if (i == 2)
        final.setText("Bot win!");
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

void Field2::reset() {
    counterBot = 0;
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
            vecFieldBot[i][j] = 0;
        }
    }
}

bool Field2::isRowWin(int i) {
    if (vecFieldBot[0][0] == i && vecFieldBot[0][1] == i && vecFieldBot[0][2] == i) return true;
    if (vecFieldBot[1][0] == i && vecFieldBot[1][1] == i && vecFieldBot[1][2] == i) return true;
    if (vecFieldBot[2][0] == i && vecFieldBot[2][1] == i && vecFieldBot[2][2] == i) return true;
    return false;
}

bool Field2::isColWin(int i) {
    if (vecFieldBot[0][0] == i && vecFieldBot[1][0] == i && vecFieldBot[2][0] == i) return true;
    if (vecFieldBot[0][1] == i && vecFieldBot[1][1] == i && vecFieldBot[2][1] == i) return true;
    if (vecFieldBot[0][2] == i && vecFieldBot[1][2] == i && vecFieldBot[2][2] == i) return true;
    return false;
}

bool Field2::isDiagWin(int i) {
    if (vecFieldBot[0][0] == i && vecFieldBot[1][1] == i && vecFieldBot[2][2] == i) return true;
    if (vecFieldBot[0][2] == i && vecFieldBot[1][1] == i && vecFieldBot[2][0] == i) return true;
    return false;
}

int Field2::isWin() {
    if (isRowWin(1) || isColWin(1) || isDiagWin(1)) finalWidget(1);
    if (isRowWin(2) || isColWin(2) || isDiagWin(2)) finalWidget(2);
    if (counterBot == 9) finalWidget(0);
    return 0;
}

void Field2::bot() {
    int x = 0;
    int y = 0;
    srand(time(NULL));
    int random = abs(rand() % 9);
    while (vecFieldBot[x][y] != 0) {
        x = random / 3;
        y = random % 3;
        random = abs(rand() % 9);
    }
    vecFieldBut[x * 3 + y]->setText("o");
    vecFieldBot[x][y] = 2;
    counterBot++;
    isWin();
}

void Field2::on_pushButton1_1_clicked()
{
    if (vecFieldBot[0][0] == 0) {
        ui->pushButton1_1->setText("x");
        vecFieldBot[0][0] = 1;
        counterBot++;
    }
    if (!isWin())
        bot();
}

void Field2::on_pushButton1_2_clicked()
{
    if (vecFieldBot[0][1] == 0) {
        ui->pushButton1_2->setText("x");
        vecFieldBot[0][1] = 1;
        counterBot++;
    }
    if (!isWin())
        bot();
}

void Field2::on_pushButton1_3_clicked()
{
    if (vecFieldBot[0][2] == 0) {
        ui->pushButton1_3->setText("x");
        vecFieldBot[0][2] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton2_1_clicked()
{
    if (vecFieldBot[1][0] == 0) {
        ui->pushButton2_1->setText("x");
        vecFieldBot[1][0] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton2_2_clicked()
{
    if (vecFieldBot[1][1] == 0) {
        ui->pushButton2_2->setText("x");
        vecFieldBot[1][1] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton2_3_clicked()
{
    if (vecFieldBot[1][2] == 0) {
        ui->pushButton2_3->setText("x");
        vecFieldBot[1][2] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton3_1_clicked()
{
    if (vecFieldBot[2][0] == 0) {
        ui->pushButton3_1->setText("x");
        vecFieldBot[2][0] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton3_2_clicked()
{
    if (vecFieldBot[2][1] == 0) {
        ui->pushButton3_2->setText("x");
        vecFieldBot[2][1] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

void Field2::on_pushButton3_3_clicked()
{
    if (vecFieldBot[2][2] == 0) {
        ui->pushButton3_3->setText("x");
        vecFieldBot[2][2] = 1;
        counterBot++;
    }
    if (!isWin())
    bot();
}

