#include "matrix_t.h"

#include <iostream>

double &s21::matrix_t::operator()(size_t i, size_t j) { return matrix[i][j]; }

const double &s21::matrix_t::operator()(size_t i, size_t j) const {
  return matrix[i][j];
}

void s21::matrix_t::moveXYZ(double x, double y, double z) {
  for (size_t i = 0; i != rows; ++i) {
    matrix[i][0] += x;
    matrix[i][1] += y;
    matrix[i][2] += z;
  }
}

void s21::matrix_t::zoom(double zoom) {
  for (size_t i = 0; i != rows; ++i) {
    for (size_t j = 0; j != cols; ++j) {
      matrix[i][j] *= zoom;
    }
  }
}

s21::matrix_t s21::matrix_t::initRotationMatrixXYZ(double alpha, double beta,
                                                   double gamma) {
  rows = 3;
  cols = 3;
  matrix = {{cos(beta) * cos(gamma),
             sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma),
             cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma)},
            {cos(beta) * sin(gamma),
             sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma),
             cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma)},
            {-sin(beta), sin(alpha) * cos(beta), cos(alpha) * cos(beta)}};
  return *this;
}

void s21::matrix_t::rotationXYZ(double alpha, double beta, double gamma) {
  alpha = alpha * M_PI / 180;
  beta = beta * M_PI / 180;
  gamma = gamma * M_PI / 180;
  matrix_t rotation;
  this->mulMatrix(rotation.initRotationMatrixXYZ(alpha, beta, gamma));
}

void s21::matrix_t::mulMatrix(const matrix_t &other) {
  matrix_t result;
  for (size_t k = 0; k != rows; ++k) {
    result.prepareRow();
    for (size_t i = 0; i != other.getCols(); ++i) {
      double sum = 0;
      for (size_t j = 0; j != other.getRows(); ++j) {
        sum += matrix[k][j] * other(j, i);
      }
      result(k, i) = sum;
    }
  }
  matrix = result.matrix;
}

void s21::matrix_t::prepareRow() { matrix.push_back(std::vector<double>(3)); }
