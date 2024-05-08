#include <w2v/config.h>

namespace w2v {

Config::Config()
    : min_count(5), 
      t(1e-4),
      dim(100) {}

void Config::set(const std::unordered_map<std::string, std::vector<std::string> >& params) {
    this->params = params;

    if (has("alpha")) {
        alpha = get_double("double");
    }
    if (has("train_file")) {
        train_file = get_string("train_file");
    }
    if (has("output")) {
        output = get_string("output");
    }
    if (has("window")) {
        window = get_int("window");
    }
    if (has("min_count")) {
        min_count = get_int("min_count");
    }
    if (has("verbose")) {
        verbose = get_bool("verbose");
    }
    if (has("t")) {
        t = get_double("t");
    }
    if (has("dim")) {
        dim = get_int("dim");
    }
}

bool Config::has(const std::string& key) {
    return params.count(key) > 0 && params[key].size() > 0;
}

int Config::get_int(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return 0;
    }
    return std::stoi(params[key][0]);
}

long Config::get_long(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return 0;
    }
    return std::stol(params[key][0]);
}

unsigned long Config::get_ulong(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return 0;
    }
    return std::stoul(params[key][0]);
}

double Config::get_double(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return 0.;
    }
    return std::stod(params[key][0]);
}

bool Config::get_bool(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return false;
    }
    std::string value  = params[key][0];
    return value == "true";
}

std::string Config::get_string(const std::string& key) {
    if(params.count(key) == 0 || params[key].size() == 0) {
        return std::string("");
    }
    return params[key][0];
}


}