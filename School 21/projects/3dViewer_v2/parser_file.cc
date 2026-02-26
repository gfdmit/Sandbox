#include "parser_file.h"

void s21::ParserFile::parseFile(const std::string &fileName, data &data) {
    std::ifstream file;
    std::string line;
    file.open(fileName);
    while (getline(file, line)) {
        if (line.front() == 'v') parseVertex(line.substr(1, line.size()), data);
        if (line.front() == 'f') parseFacet(line.substr(1, line.size()), data);
    }
    data.matrix_3d.setCols(3);
    data.matrix_3d.setRows(data.count_of_vertexes);
    file.close();
}

void s21::ParserFile::parseVertex(const std::string &line, data& data) {
    std::stringstream str(line);
    std::string token;
    data.matrix_3d.prepareRow();
    for (int i = 0; str >> token && i != 3; ++i) {
        data.matrix_3d(data.count_of_vertexes, i) = std::stod(token);
    }
    data.count_of_vertexes++;
}

void s21::ParserFile::parseFacet(const std::string &line, data& data) {
    std::stringstream str(line);
    std::string token;
    data.preparePolygon();
    for (int i = 0; str >> token; ++i) {
        data.polygons[data.count_of_facets].number_of_vertexes_in_facets++;
        data.polygons[data.count_of_facets].vertexes.push_back(std::stod(token));
    }
    data.count_of_facets++;
}

void s21::ParserFile::printMatrix(const data &data) {
    for (int i = 0; i != data.count_of_vertexes; ++i) {
        std::cout << data.matrix_3d(i, 0) << " " 
                  << data.matrix_3d(i, 1) << " "
                  << data.matrix_3d(i, 2) << std::endl;
    }
}
