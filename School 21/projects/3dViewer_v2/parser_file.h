#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_PARSERFILE_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_PARSERFILE_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "matrix_t.h"
#include "structs.h"

namespace s21 {

class ParserFile {
 private:
  void parseVertex(const std::string &line, data &data);
  void parseFacet(const std::string &line, data &data);

 public:
  ParserFile() = default;
  ~ParserFile() = default;
  void parseFile(const std::string &fileName, data &data);
  void printMatrix(const data &data);
};

}  // namespace s21

#endif