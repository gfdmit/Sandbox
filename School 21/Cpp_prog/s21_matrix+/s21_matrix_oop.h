#pragma once

#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
class S21Matrix {
    private:
        size_t rows_, cols_;
        std::vector<std::vector<T>> matrix_;
    
    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();

        size_t GetRows() const;
        size_t GetCols() const;

        template <typename T2>
        bool EqMatrix(const S21Matrix<T2>& other);
        template <typename T2>
        void SumMatrix(const S21Matrix<T2>& other); 
        template <typename T2>
        void SubMatrix(const S21Matrix<T2>& other);
        void MulNumber(const double num);
        template <typename T2>
        void MulMatrix(const S21Matrix<T2>& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();

        template <typename T2>
        S21Matrix operator + (const S21Matrix<T2>& matrix) const;
        template <typename T2>
        S21Matrix operator - (const S21Matrix<T2>& matrix) const;
        template <typename T2>
        S21Matrix operator * (const S21Matrix<T2>& matrix) const;
        S21Matrix operator * (const double num);
        
        template <typename T2>
        bool operator == (const S21Matrix<T2>& matrix);
        template <typename T2>
        bool operator != (const S21Matrix<T2>& matrix);
        template <typename T2>
        S21Matrix operator = (const S21Matrix<T2>& matrix);
        template <typename T2>
        S21Matrix operator = (S21Matrix<T2>&& matrix);
        template <typename T2>
        S21Matrix& operator += (const S21Matrix<T2>& matrix);
        template <typename T2>
        S21Matrix& operator -= (const S21Matrix<T2>& matrix);
        template <typename T2>
        S21Matrix& operator *= (const S21Matrix<T2>& matrix);
        S21Matrix& operator *= (const double num);
        
        T& operator () (size_t i, size_t j);
        const T& operator () (size_t i, size_t j) const;
};

template <typename T>
std::ostream& operator << (std::ostream& out, const S21Matrix<T>& matrix);

template <typename T>
std::istream& operator >> (std::istream& in, S21Matrix<T>& matrix);

template <typename T>
double MinorDeterminant(int i_index, int j_index, S21Matrix<T> matrix);