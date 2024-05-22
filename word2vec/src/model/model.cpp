#include <w2v/model.h>
#include <cmath>
#include <numeric>

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

void Model::init(const std::vector<int64_t>& counts) {
    double power = 0.75;
    double z = std::accumulate(
        counts.begin(), 
        counts.end(), 0., 
        [&power](double acc, double x) { return acc + pow(x, power); });

    for (size_t i = 0, size = counts.size(); i < size; i++) {
        double c = counts[i] / z * NEGATIVE_TABLE_SIZE;
        for (int j = 0; j < c; j++) {
            negatives_.push_back(i);
        }
    }
}

}