#ifndef W2V_MODEL_H
#define W2V_MODEL_H
#include <w2v/math/matrix.h>

#include <cstdint>
#include <memory>

namespace w2v {

class Model {

public:
    Model(int64_t n_input, int64_t n_output, int64_t dim);

private:
    int64_t n_input_;
    int64_t n_output_;
    int64_t dim_;

    std::shared_ptr<Matrix> wi_;
    std::shared_ptr<Matrix> wo_;

};  // end of class Model
}  // eno of w2v

#endif