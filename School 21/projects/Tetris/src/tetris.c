#include <ncurses.h>
#include <s21_matrix.h>
#include <stdlib.h>

void printField(matrix_t matrix) {
  for (int i = 0; i != matrix.rows; ++i) {
    for (int j = 0; j != matrix.cols; ++j) {
      if (matrix[i][j] == 1) {
        printw("*");
      } else {
        printw(" ");
      }
    }
  }
}

int main() {
  initscr();
  printw("Hello world"); // вывод строки
  refresh();             // обновить экран
  getch();
  endwin();
}