#include <w2v/model.h>

namespace w2v {

Model::Model(int64_t n_input, int64_t n_output, int64_t dim) {
    n_input_ = n_input;
    n_output_ = n_output;
    dim_ = dim;

    wi_ = std::make_shared<Matrix>(n_input_, dim_);
    wi_->uniform();

    wo_ = std::make_shared<Matrix>(n_output_, dim_);
    wo_->zero();
}

}