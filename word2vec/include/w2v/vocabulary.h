#ifndef W2V_VOCABULARY_H  
#define W2V_VOCABULARY_H
#include <string>
#include <unordered_map>
#include <cstring>

namespace w2v {

class Vocabulary {
public:
    // Vocabulary(const std::string& file_path): data_file(file_path) {}
    Vocabulary();
    struct Word {
        std::string word;
        int count;
    };
    // Vocabulary() = default;

    void learn_from_file(const std::string& file_path);

    void add_word(const std::string& word);
    void add_word(const char* word);
    
    // std::size_t vocab_size();
private:
    void ReadWord(char *word, FILE *fin, char *eof) {
    int a = 0, ch;
    while (1) {
        ch = fgetc_unlocked(fin);
        if (ch == EOF) {
        *eof = 1;
        break;
        }
        if (ch == 13) continue;
        if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
        if (a > 0) {
            if (ch == '\n') ungetc(ch, fin);
            break;
        }
        if (ch == '\n') {
            strcpy(word, (char *)"</s>");
            return;
        } else continue;
        }
        word[a] = ch;
        a++;
        if (a >= MAX_STRING - 1) a--;   // Truncate too long words
    }
    word[a] = 0;
}
private:
    std::unordered_map<std::size_t, Word> word_table;

    // std::size_t vocab_size;
    std::size_t train_word;
    std::size_t vocab_size;
    const int MAX_STRING = 100;
};
}
#endif