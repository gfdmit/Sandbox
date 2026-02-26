#include "parser_file.h"

int main() {
    std::string file = "cube.obj";
    s21::data data;
    s21::ParserFile parser;
    parser.parseFile(file, data);
    parser.printMatrix(data);
    std::cout << std::endl;
    data.matrix_3d.rotationXYZ(90, 90, 90);
    parser.printMatrix(data);
}