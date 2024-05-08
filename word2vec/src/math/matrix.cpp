#include <w2v/math/matrix.h>

namespace w2v {

Matrix::Matrix(): Matrix(0, 0) {}

Matrix::Matrix(int64_t m, int64_t n)
    : m_(m),
      n_(n), 
      data_(m * n) {}

}