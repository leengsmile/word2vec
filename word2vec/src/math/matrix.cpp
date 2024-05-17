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

void Matrix::uniform(real a = 0.1) {
    std::minstd_rand rng();
    std::uniform_real_distribution<real> uniform(-a, a);
    auto gen = [&uniform]() { return uniform(rng); };
    std::generate(data_.begin(), data_.end(), gen);
}

}
