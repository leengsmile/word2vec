#include <w2v/math/vector.h>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cmath>
#include <numeric>

namespace w2v {

Vector::Vector(int64_t m)
    : data_(m) {}

Vector::Vector(Vector&& other) noexcept
    : data_(std::move(other.data_)) {}

Vector& Vector::operator=(Vector&& other) {
    if (this != &other) {
        data_ = std::move(other.data_);
    }
    return *this;
}

void Vector::zero() {
    std::fill(data_.begin(), data_.end(), float(0.));
}

void Vector::mul(real c) {
   /*
    std::transform(
        data_.begin(), 
        data_.end(), 
        data_.begin(), 
        [&](real x) {return x * c;});
   */
    // or 
    std::transform(
        data_.begin(), 
        data_.end(), 
        data_.begin(), 
        std::bind(std::multiplies<>(), std::placeholders::_1, c)
    );
}
real Vector::norm() const {
    real sum_of_square = std::inner_product(data_.begin(), data_.end(), data_.begin(), 0.);
    return std::sqrt(sum_of_square);
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << std::setprecision(5);
    for (const auto & t: v.data_) {
        os << t << ' ';
    }
    return os;
}
}  // end of namespace w2v