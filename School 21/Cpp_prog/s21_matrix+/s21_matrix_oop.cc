#include "s21_matrix_oop.h"

template <typename T>
S21Matrix<T>::S21Matrix() {
    rows_ = 1;
    cols_ = 1;
    matrix_ = std::vector<std::vector<T>>(1, std::vector<T>(1));
}

template <typename T>
S21Matrix<T>::S21Matrix(int rows, int cols) {
    if (rows < 1 || cols < 1) {
        throw std::out_of_range("Incorrect input, rows and cols must be possitive");
    }
    rows_ = rows;
    cols_ = cols;
    matrix_ = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
}

template <typename T>
S21Matrix<T>::S21Matrix(const S21Matrix& other) {
    rows_ = other.GetRows();
    cols_ = other.GetCols();
    matrix_ = std::vector<std::vector<T>>(other.GetRows(), std::vector<T>(other.GetCols()));
    for (size_t i = 0; i != other.GetRows(); ++i) {
        for (size_t j = 0; j != other.GetCols(); ++j) {
            matrix_[i][j] = other(i, j);
        }
    }
}

template <typename T>
S21Matrix<T>::S21Matrix(S21Matrix&& other) {
    rows_ = other.GetRows();
    cols_ = other.GetCols();
    matrix_ = other.matrix_;
    
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = std::vector<std::vector<T>>(0, std::vector<T>(0));
}

template <typename T>
S21Matrix<T>::~S21Matrix() {
    rows_ = 0;
    cols_ = 0;
    matrix_ = std::vector<std::vector<T>>(0, std::vector<T>(0));
}

template <typename T>
size_t S21Matrix<T>::GetRows() const {
    return rows_;
}

template <typename T>
size_t S21Matrix<T>::GetCols() const {
    return cols_;
}

template <typename T>
template <typename T2>
bool S21Matrix<T>::EqMatrix(const S21Matrix<T2> &other) {
    bool retval = true;
    if (rows_ == other.GetRows() && cols_ == other.GetCols()) {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j) {
                if (matrix_[i][j] != other(i, j))
                    retval = false;
            }
        }
    } else {
        retval = false;
    }
    return retval;
}

template <typename T>
template <typename T2>
void S21Matrix<T>::SumMatrix(const S21Matrix<T2>& other) {
    if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }
    for (size_t i = 0; i != rows_; ++i) {
        for (size_t j = 0; j != cols_; ++j) {
            matrix_[i][j] += other(i, j);
        }
    }
}

template <typename T>
template <typename T2>
void S21Matrix<T>::SubMatrix(const S21Matrix<T2>& other) {
    if (rows_ != other.GetRows() || cols_ != other.GetCols()) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }
    for (size_t i = 0; i != rows_; ++i) {
        for (size_t j = 0; j != cols_; ++j) {
            matrix_[i][j] -= other(i, j);
        }
    }
}

template <typename T>
void S21Matrix<T>::MulNumber(const double num) {
    for (size_t i = 0; i != rows_; ++i) {
        for (size_t j = 0; j != cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
}

template <typename T>
template <typename T2>
void S21Matrix<T>::MulMatrix(const S21Matrix<T2>& other) {
    if (cols_ != other.GetRows()) {
        throw std::out_of_range("Incorrect input, rows and cols are not the same");
    }
    S21Matrix<T> result = S21Matrix<T>(rows_, other.GetCols());
    for (size_t k = 0; k != rows_; ++k) {
        for (size_t i = 0; i != other.GetCols(); ++i) {
            double sum = 0;
            for (size_t j = 0; j != other.GetRows(); ++j) {
                sum += matrix_[k][j] * other(j, i);
            }
            result(k, i) = sum;
        }
    }
    rows_ = result.rows_;
    cols_ = result.cols_;
    matrix_ = result.matrix_;
}

template <typename T>
S21Matrix<T> S21Matrix<T>::Transpose() {
    S21Matrix<T> result = S21Matrix<T>(cols_, rows_);
    for (size_t i = 0; i != rows_; ++i) {
        for (size_t j = 0; j != cols_; ++j) {
            result(j, i) = matrix_[i][j];
        }
    }
    return result;
}

template <typename T>
S21Matrix<T> S21Matrix<T>::CalcComplements() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix should be square");
    }
    S21Matrix<T> result = S21Matrix<T>(rows_, cols_);
    S21Matrix<T> minor_ = S21Matrix<T>(rows_, cols_);
    result.matrix_ = std::vector<std::vector<T>>(rows_, std::vector<T>(cols_));
    minor_.matrix_ = matrix_;
    if (rows_ != 1) {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j) {
                result(i, j) = pow(-1, i + j) * MinorDeterminant(i, j, minor_);
            }
        }
    } else {
        result(0, 0) = 1;
    }
    return result;
}

template <typename T>
double S21Matrix<T>::Determinant() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix should be square");
    }
    double result = 0;
    if (rows_ == 2) {
        result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
    } else if (rows_ == 1) {
        result = matrix_[0][0];
    } else {
        for (int i = 0; i != rows_; ++i) {
            S21Matrix<T> temp_matrix = S21Matrix<T>(rows_ - 1, cols_ - 1);
            double det = 0;
            for (int j = 1; j != rows_; ++j) {
                int match = 0;
                for (int k = 0; k != cols_; ++k) {
                    if (k != i) {
                        temp_matrix.matrix_[j - 1][k - match] = matrix_[j][k];
                    } else {
                        match = 1;
                    }
                }
            }
            det = temp_matrix.Determinant();
            result += matrix_[0][i] * pow(-1, i) * det;
        }
    }
    return result;
}

template <typename T>
S21Matrix<T> S21Matrix<T>::InverseMatrix() {
    double det = 0;
    det = this->Determinant();
    if (det == 0) {
        throw std::invalid_argument("Matrix should be square and determinant != 0");
    }
    S21Matrix<T> temp1 = S21Matrix<T>(rows_, cols_);
    S21Matrix<T> temp2 = S21Matrix<T>(rows_, cols_);
    temp1.matrix_ = this->CalcComplements().matrix_;
    temp2.matrix_ = temp1.Transpose().matrix_;
    temp2.MulNumber(1/det);
    return temp2;
}

template <typename T>
template <typename T2>
S21Matrix<T> S21Matrix<T>::operator + (const S21Matrix<T2>& matrix) const {
    S21Matrix<T> result(*this);
    result.SumMatrix(matrix);
    return result;
}

template <typename T>
template <typename T2>
S21Matrix<T> S21Matrix<T>::operator - (const S21Matrix<T2>& matrix) const {
    S21Matrix<T> result(*this);
    result.SubMatrix(matrix);
    return result;
}

template <typename T>
template <typename T2>
S21Matrix<T> S21Matrix<T>::operator * (const S21Matrix<T2>& matrix) const {
    S21Matrix<T> result(*this);
    result.MulMatrix(matrix);
    return result;
}

template <typename T>
S21Matrix<T> S21Matrix<T>::operator * (const double num) {
    S21Matrix<T> result(*this);
    result.MulNumber(num);
    return result;
}

template <typename T>
template <typename T2>
bool S21Matrix<T>::operator == (const S21Matrix<T2>& matrix) {
    S21Matrix<T> result(*this);
    return result.EqMatrix(matrix);
}

template <typename T>
template <typename T2>
bool S21Matrix<T>::operator != (const S21Matrix<T2>& matrix) {
    S21Matrix<T> result(*this);
    return !result.EqMatrix(matrix);
}

template <typename T>
template <typename T2>
S21Matrix<T> S21Matrix<T>::operator = (const S21Matrix<T2>& matrix) {
    rows_ = matrix.GetRows();
    cols_ = matrix.GetCols();
    matrix_ = std::vector<std::vector<T>>(rows_, std::vector<T>(cols_));
    for (size_t i = 0; i != matrix.GetRows(); ++i) {
        for (size_t j = 0; j != matrix.GetCols(); ++j) {
            matrix_[i][j] = matrix(i, j);
        }
    }
    return *this;
}

template <typename T>
template <typename T2>
S21Matrix<T> S21Matrix<T>::operator = (S21Matrix<T2>&& matrix) {
    rows_ = matrix.GetRows();
    cols_ = matrix.GetCols();
    matrix_ = matrix.matrix_;
    matrix.rows_ = 0;
    matrix.cols_ = 0;
    matrix.matrix_ = std::vector<std::vector<T>>(0, std::vector<T>(0));
}

template <typename T>
template <typename T2>
S21Matrix<T>& S21Matrix<T>::operator += (const S21Matrix<T2>& matrix) {
    SumMatrix(matrix);
    return *this;
}

template <typename T>
template <typename T2>
S21Matrix<T>& S21Matrix<T>::operator -= (const S21Matrix<T2>& matrix) {
    SubMatrix(matrix);
    return *this;
}

template <typename T>
template <typename T2>
S21Matrix<T>& S21Matrix<T>::operator *= (const S21Matrix<T2>& matrix) {
    MulMatrix(matrix);
    return *this;
}

template <typename T>
S21Matrix<T>& S21Matrix<T>::operator *= (const double num) {
    MulNumber(num);
    return *this;
}

template <typename T>
T& S21Matrix<T>::operator () (size_t i, size_t j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

template <typename T>
const T& S21Matrix<T>::operator () (size_t i, size_t j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i][j];
}

template <typename T>
std::ostream& operator << (std::ostream& out, const S21Matrix<T>& matrix) {
    for (size_t i = 0; i != matrix.GetRows(); ++i) {
        for (size_t j = 0; j != matrix.GetCols(); ++j) {
            if (j > 0) {
                out << "\t";
            }
            out << matrix(i, j);
        }
        out << "\n";
    }
    return out;
}
 
template <typename T>
std::istream& operator >> (std::istream& in, S21Matrix<T>& matrix) {
    for (size_t i = 0; i != matrix.GetRows(); ++i) {
        for (size_t j = 0; j != matrix.GetCols(); ++j) {
            in >> matrix(i, j);
        }
    }
    return in;
}

template <typename T>
double MinorDeterminant(int i_index, int j_index, S21Matrix<T> matrix) {
    if (matrix.GetRows() != matrix.GetCols()) {
        throw std::invalid_argument("Matrix should be square");
    }
    S21Matrix<T> minor_ = S21Matrix<T>(matrix.GetRows() - 1, matrix.GetCols() - 1);
    int match_i = 0;
    for (int i = 0; i != matrix.GetRows(); ++i) {
        if (i == i_index) {
            match_i = 1;
        }
        int match_j = 0;
        for (int j = 0; j != matrix.GetCols() && i != i_index; ++j) {
            if (j != j_index) {
                minor_(i - match_i, j - match_j) = matrix(i, j);
            } else {
                match_j = 1;
            }
        }
    }
    double det = 0;
    det = minor_.Determinant();
    return det;
}
