#include <w2v/vocabulary.h>
#include <w2v/utils/common.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace w2v {

const std::string Vocabulary::EOS = "</s>";
const std::string Vocabulary::BOW = "<";
const std::string Vocabulary::EOW = ">";


Vocabulary::Vocabulary(std::shared_ptr<Config> config)
    : config_(config),
      ntokens_(0),
      nwords_(0),
      size_(0),
      word2int_(MAX_VOCAB_SIZE, -1) {
}

void Vocabulary::learn_from_file(const std::string& file_path) {
    
    // std::ifstream in(file_path, std::ifstream::in | std::ifstream::binary);
    std::ifstream in(file_path, std::ifstream::in | std::ifstream::binary);
    // std::cout << "file path: " << file_path << ", " << in.is_open() << std::endl;
    std::string word;
    int64_t min_threshold = 1;
    while (read_word(in, word)) {
        add_word(word);
        // std::cout << "add word: " << word << ", #tokens = " << ntokens_  << ", #words " << size_ << std::endl;
        if (ntokens_ % 1000000 == 0 && config_->verbose) {
            std::cerr << "\rRead " << ntokens_ / 1000000 << "M words" << std::flush;
        }
        if (size_ > 0.75 * MAX_VOCAB_SIZE) {
            min_threshold++;
            threshold(min_threshold);

        }
    }
    // std::cout << "add word: " << word << ", #tokens = " << ntokens_  << ", #words " << size_ << std::endl;

    threshold(config_->min_count);
    in.close();
    if (config_->verbose) {
        std::cerr << "\rWords in train file:  " << ntokens_ << std::endl;
        std::cerr << "Number of words:  " << nwords_ << std::endl;
    }
}

bool Vocabulary::read_word(std::istream& in, std::string& word) {
    std::streambuf& sb = *in.rdbuf();
    int c;
    word.clear();
    while ((c = sb.sbumpc()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' ||
            c == '\f' || c == '\0') {
            if (word.empty()) {
                if (c == '\n') {
                    word += EOS;
                    return true;
                }
                continue;
            } else {
                if (c == '\n') {
                    sb.sungetc();
                }
                return true;
            }

        }
        word.push_back(c);
    }
    // trigger eofbit for stream `in`
    in.get();
    return !word.empty();
}


void Vocabulary::add_word(const std::string& w) {
    ntokens_++;
    int32_t h = find(w);
    if (word2int_[h] == -1) {
        Entity e {w, 1};
        words_.emplace_back(std::move(e));
        word2int_[h] = size_++;
    } else {
        words_[word2int_[h]].count++;
    }
}

void Vocabulary::threshold(int64_t t) {
    // std::cout << "\rthreshold t = " << t << ", size = " << size_ << ", ntokens = " << ntokens_ << std::endl;
    std::sort(words_.begin(), words_.end(), 
              [](const Entity& e1, const Entity& e2) {return e1.count > e2.count;});
    words_.erase(
        std::remove_if(
            words_.begin(), 
            words_.end(), 
            [&](const Entity& e) {
                return e.count < t;
            }
        ), 
        words_.end()
    );
    words_.shrink_to_fit();
    size_ = 0;
    nwords_ = 0;
    std::fill(word2int_.begin(), word2int_.end(), -1);
    for (auto it = words_.begin(); it != words_.end(); ++it) {
        int32_t h = find(it->word);
        word2int_[h] = size_++;
        nwords_++;
    }
}

int32_t Vocabulary::nwords() const {
    return nwords_;
}

int64_t Vocabulary::ntokens() const {
    return ntokens_;
}

int32_t Vocabulary::find(const std::string& word) const {
    return find(word, common::hash(word));
}

int32_t Vocabulary::find(const std::string& word, uint32_t h) const {
    int32_t w2i_size = word2int_.size();
    int32_t id = h % w2i_size;
    while (word2int_[id] != -1 && words_[word2int_[id]].word != word) {
        id = (id + 1) % w2i_size;
    }
    return id;
}



}  // eno of namespace w2v