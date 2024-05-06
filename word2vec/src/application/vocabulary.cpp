#include <w2v/vocabulary.h>
#include <w2v/utils/common.h>

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <vector>

namespace w2v {

Vocabulary::Vocabulary(): train_word(0) {
}

void Vocabulary::learn_from_file(const std::string& file_path) {
    auto start(std::chrono::high_resolution_clock::now());
    // auto fin = fopen(file_path.c_str(), "rb");
    // char word[MAX_STRING];
    // char eof;
    // vocab_size = 0;
    // while (true) {
    //     ReadWord(word, fin, &eof);
    //     if (eof) {
    //         break;
    //     }
    //     train_word++;
    //     std::cout << train_word << ": " << word << std::endl;
    //     add_word(word);
    // }
    // fclose(fin);
    std::ifstream in(file_path, /*std::ifstream::in |*/ std::ifstream::binary);
    std::string word;
    while (in >> word) {
        // std::cout << word << std::endl;
        add_word(word);
        train_word++;
        // word.clear();
    }
    // in.close();
    auto end(std::chrono::high_resolution_clock::now());
    auto elapsed = (end - start) / std::chrono::milliseconds(1);
    std::cout << "Vocab size: " << vocab_size << std::endl;
    std::cout << "Words in train file: " << train_word << std::endl;
    std::cout << "Elpsed: " << elapsed << std::endl;

    std::ofstream out("vocab", std::fstream::out);
    for (const auto& entry: word_table) {
        std::vector<std::string> tokens;
        tokens.push_back(entry.second.word);
        tokens.push_back(std::to_string(entry.second.count));
        std::string line = common::join(tokens, "\t");
        out << line << std::endl;
    }
    out.close();
    
}

void Vocabulary::add_word(const std::string& word) {
    std::size_t hash = common::hash(word.c_str());
    auto iter = word_table.find(hash);
    if ( iter != word_table.end()) {
        iter->second.count++;
    } else {
        Word w {std::move(word), 1};
        word_table.insert({hash, w});
        vocab_size++;
    }
}


void Vocabulary::add_word(const char* word) {
    std::size_t hash = common::hash(word);
    auto iter = word_table.find(hash);
    if ( iter != word_table.end()) {
        iter->second.count++;
    } else {
        Word w {"", 1};
        word_table.insert({hash, w});
        vocab_size++;
    }
}

}