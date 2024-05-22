#ifndef W2V_CONFIG_H
#define W2V_CONFIG_H
#include <unordered_map>
#include <string>
#include <vector>

namespace w2v {

enum class model_type: int { cbow = 1, sg };
enum class loss_type: int { hs = 1, ns };

struct Config {

public:
    double alpha;
    std::string output;
    std::string train_file;
    int window;

    int64_t min_count;
    bool verbose;

    double t;
    int dim;

    int num_threads;
    int epoch;
        
    Config();
    virtual ~Config() {}

    virtual void set(const std::unordered_map<std::string, std::vector<std::string> >& params);

private:
    std::unordered_map<std::string, std::vector<std::string> > params;

    bool has(const std::string& key);

    int get_int(const std::string& key);
    long get_long(const std::string& key);
    unsigned long get_ulong(const std::string& key);
    double get_double(const std::string& key);
    bool get_bool(const std::string& key);
    std::string get_string(const std::string& key);
};

}  // end of w2v

#endif