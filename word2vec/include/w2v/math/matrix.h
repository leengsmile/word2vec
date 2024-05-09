#ifndef W2V_MATRIX_H
#define W2V_MATRIX_H
#include <w2v/types.h>
#include <cstdint>
#include <vector>

namespace w2v {

class Vector;

class Matrix {

public:
    Matrix();
    Matrix(int64_t m, int64_t n);
    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = delete;
    
private:
    std::vector<real> data_;
    int64_t m_;
    int64_t n_;

};

}  // end of namespace w2v
#endif