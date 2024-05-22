#include <w2v/math/matrix.h>
#include <algorithm>
#include <random>

namespace w2v {

Matrix::Matrix(): Matrix(0, 0) {}

Matrix::Matrix(int64_t m, int64_t n)
    : m_(m),
      n_(n), 
      data_(m * n) {}

void Matrix::zero() {
    std::fill(data_.begin(), data_.end(), 0.);
}

void Matrix::uniform(real a) {
    std::minstd_rand rng(1234);
    std::uniform_real_distribution<> uniform(-a, a);
    auto gen = [&uniform, &rng]() { return uniform(rng); };
    std::generate(data_.begin(), data_.end(), gen);  //
}

}
