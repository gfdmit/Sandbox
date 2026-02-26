#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_

#include "matrix_t.h"

namespace s21 {

struct polygon_t {
    std::vector<int> vertexes;
    size_t number_of_vertexes_in_facets;
    polygon_t() : number_of_vertexes_in_facets(0){}
};

struct data {
    size_t count_of_vertexes;
    size_t count_of_facets;
    s21::matrix_t matrix_3d;
    std::vector<polygon_t> polygons;
    data() : count_of_vertexes(0), count_of_facets(0){}
    void preparePolygon() { polygons.push_back(polygon_t()); }
};

} // namespace s21

#endif // CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_