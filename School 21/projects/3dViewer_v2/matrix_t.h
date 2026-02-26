#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_

#include <vector>
#include <cstddef>
#include <cmath>

namespace s21 {

class matrix_t {
private:
    std::vector<std::vector<double>> matrix;
    size_t rows;
    size_t cols;
public:
    matrix_t() : cols(0), rows(0) {};
    ~matrix_t() = default;
    void prepareRow();

    void moveXYZ(double x, double y, double z);

    s21::matrix_t initRotationMatrixXYZ(double alpha, double beta, double gamma);
    void rotationXYZ(double alpha, double beta, double gamma);

    void zoom(double zoom);

    void mulMatrix(const matrix_t &other);

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    void setRows(size_t row) { rows = row; }
    void setCols(size_t col) { cols = col; }

    double &operator()(size_t i, size_t j);
    const double &operator()(size_t i, size_t j) const;
};

} // namespace s21


#endif // CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_