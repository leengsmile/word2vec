#ifndef W2V_MODEL_H
#define W2V_MODEL_H
#include <w2v/math/matrix.h>

#include <cstdint>
#include <memory>
#include <vector>

namespace w2v {

class Model {

    // table to hold indices used for negative sampling
    static const int32_t NEGATIVE_TABLE_SIZE = 10000000;

public:
    Model(int64_t n_input, int64_t n_output, int64_t dim);

    void init(const std::vector<int64_t>& counts);
    
private:
    int64_t n_input_;
    int64_t n_output_;
    int64_t dim_;

    std::shared_ptr<Matrix> wi_;
    std::shared_ptr<Matrix> wo_;

    std::vector<int32_t> negatives_;

};  // end of class Model
}  // eno of w2v

#endif