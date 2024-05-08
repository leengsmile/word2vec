#ifndef W2V_VECTOR_H
#define W2V_VECTOR_H

#include <w2v/types.h>
#include <cstdint>
#include <vector>

namespace w2v {

class Matrix;

class Vector {

public:
    explicit Vector(int64_t m);
    Vector(const Vector&) = delete;
    Vector(Vector&&) noexcept;
    Vector& operator=(const Vector&) = delete;
    Vector& operator=(Vector&&);
    
    inline real& operator[](int64_t i) {
        return data_[i];
    }

    inline const real& operator[](int64_t i) const {
        return data_[i];
    }

    inline int64_t size() const {
        return data_.size();
    }

    void zero();

    void mul(real c);

    real norm() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

private:
    std::vector<float> data_;
};



}  // end of namespace w2v
#endif
