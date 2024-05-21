#include <w2v/application.h>
#include <w2v/config.h>
#include <w2v/utils/common.h>
#include <w2v/utils/stream.h>

#include <iostream>
#include <fstream>
#include <thread>

namespace w2v {

Application::Application(int argc, char** argv) {
    load_parameters(argc, argv);
}

Application::~Application() {

}

void Application::run() {
    vocab_ = std::make_shared<Vocabulary>(config_);
    vocab_->learn_from_file(config_->train_file);

    input_ = std::make_shared<Matrix>(vocab_->nwords(), config_->dim);
    input_->uniform(1.0 / config_->dim);

    output_ = std::make_shared<Matrix>(vocab_->nwords(), config_->dim);
    output_->zero();

    std::vector<std::thread> threads;
    for (int32_t i = 0; i < config_->num_threads; i++) {
        threads.push_back(std::thread(
            [=](){ train_thread(i); }
        ));
    }

    const int64_t ntokens = vocab_->ntokens();
    int64_t local_tokens = 0;
    
    while (total_count_ < config_->epoch * ntokens) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        if (config_->verbose) {
            real progress = real(total_count_) / (config_->epoch * ntokens);
        }
    }

    for (int32_t i = 0; i < config_->num_threads; i++) {
        threads[i].join();
    }

}

void Application::load_parameters(int argc, char** argv) {
    
    std::unordered_map<std::string, std::string> params;
    std::unordered_map<std::string, std::vector<std::string> > all_params;
    
    std::string current_key("");
    all_params[current_key];  // positional arguments
    // int i = 0;
    const std::string dash("-");
    std::vector<std::string> args(argv, argv+argc);
    for (const auto & str: args) {
        std::string str_t = common::ltrim(str, '-');
        if (!str.compare(str_t)) {
            all_params[current_key].push_back(str_t);
        } else {
            current_key = str_t;
        }
    }

    for (const auto & pair: all_params) {
        if (!pair.second.empty()) {
            params[pair.first] = pair.second[0];
        }
    }
    // config_ = std::make_shared<Config>();
    config_.reset(new Config());
    config_->set(all_params);
}

void Application::train_thread(int32_t thread_id) {
    std::ifstream in(config_->train_file);
    common::seek(in, thread_id * common::size(in) / config_->num_threads);
}

}