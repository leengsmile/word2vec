#include <w2v/application.h>
#include <w2v/config.h>
#include <w2v/utils/common.h>

#include <iostream>
#include <fstream>

namespace w2v {

Application::Application(int argc, char** argv) {
    load_parameters(argc, argv);
}

Application::~Application() {

}
void Application::run() {
    vocab_ = std::make_shared<Vocabulary>(config_);
    // std::cout << "vocab finished." << std::endl;
    vocab_->learn_from_file(config_->train_file);
    
    // std::hash<std::string> hash;
    // std::string str("Hello");
    // std::string str2("Hello");
    // std::cout << "hash(" << str << "):" << hash(str) << std::endl;
    // std::cout << "hash(" << str2 << "):" << hash(str2) << std::endl;
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
    config_ = std::make_shared<Config>();
    // std::cout << "Finished config" << std::endl;
    config_->set(all_params);
}

}