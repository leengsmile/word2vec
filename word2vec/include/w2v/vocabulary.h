#ifndef W2V_VOCABULARY_H  
#define W2V_VOCABULARY_H
#include <w2v/config.h>
#include <w2v/types.h>
#include <string>
#include <unordered_map>
#include <cstring>
#include <memory>
#include <vector>
#include <random>

namespace w2v {

struct Entity {
    std::string word;
    int64_t count;
};

class Vocabulary {
public:
    static const std::string EOS;
    static const std::string BOW;
    static const std::string EOW;

    Vocabulary(std::shared_ptr<Config> config);

    void learn_from_file(const std::string& file_path);

    bool read_word(std::istream& in, std::string& word);
    void add_word(const std::string& word);

    void threshold(int64_t t);

    int32_t nwords() const;

    int64_t ntokens() const;

    std::vector<int64_t> get_counts() const;

    void reset(std::istream& in) const;
    int32_t get_line(std::istream& in, std::vector<int32_t>& words, std::minstd_rand& rng);
    // void add_word(const char* word);

    // uint32_t hash(const std::string& w) const;
    
    // std::size_t vocab_size();
    
private:
    // static const int32_t MAX_VOCAB_SIZE = 30000000; 
    static const int32_t MAX_VOCAB_SIZE = 30000000; 
    static const int32_t MAX_LINE_SIZE = 1024;
    

    std::shared_ptr<Vocabulary> vocab_;
    int64_t ntokens_;
    int32_t nwords_;
    int32_t size_;

    std::vector<int32_t> word2int_;
    std::vector<Entity> words_;
    std::vector<real> pdiscard_;


    std::shared_ptr<Config> config_;

    // std::size_t vocab_size;
    std::size_t train_word;
    std::size_t vocab_size;
    const int MAX_STRING = 100;

private:
    int32_t find(const std::string& word) const;
    int32_t find(const std::string& word, uint32_t h) const;
    
    void init_discard_table();
    bool discard(int32_t id, real rand);

};  // end of Vocabulary
}  // end of w2v
#endif