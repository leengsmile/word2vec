#ifndef W2V_COMMON_H
#define W2V_COMMON_H

#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

namespace w2v {

namespace common {

inline static char tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - ('Z' - 'z');
    }
    return c;
}

inline static std::string trim(std::string& str) {
    std::string ret(str);
    if (str.empty()) {
        return ret;
    }
    ret.erase(ret.find_last_not_of(" \f\n\r\t\v") + 1);
    ret.erase(0, ret.find_first_not_of(" \f\n\r\t\v"));
    return ret;
}

inline static std::string ltrim(std::string& str) {
    std::string ret(str);
    if (ret.empty()) {
        return ret;
    }
    ret.erase(0, ret.find_first_not_of(" \f\n\r\t\v"));
    return ret;
}

inline static std::string ltrim(const std::string& str, const char c) {
    std::string ret(str);
    if (str.empty()) {
        return ret;
    }
    ret.erase(0, ret.find_first_not_of(c));
    return ret;
}

inline static std::string join(const std::vector<std::string>& strs, const char* delimiter) {
    if (strs.empty()) {
        return std::string("");
    }
    std::ostringstream oss;
    oss << std::setprecision(std::numeric_limits<double>::digits10 + 2);
    oss << strs[0];
    for (size_t i = 1; i < strs.size(); ++i) {
        oss << delimiter << strs[i];
    }
    return oss.str();
}

inline static std::vector<std::string> split(const char* c_str, const char& delimiter) {
    std::vector<std::string> ret;
    std::string str(c_str);

    size_t i = 0;
    size_t pos = str.find(delimiter);
    while (pos != std::string::npos) {
        ret.push_back(str.substr(i, pos - i));
        i = ++pos;
        pos = str.find(delimiter, pos);
    }
    ret.push_back(str.substr(i));
    return ret;
}

inline static std::vector<std::string> split(const char* c_str, const char* delimiter) {
    std::vector<std::string> ret;
    std::string str(c_str);

    size_t i = 0;
    size_t pos = str.find_first_of(delimiter);
    while (pos != std::string::npos) {
        ret.push_back(str.substr(i, pos - i));
        i = ++pos;
        pos = str.find_first_of(delimiter, pos);
    }
    ret.push_back(str.substr(i));
    return ret;
}

inline static bool starts_with(const char* c_str, char delimiter) {
    return c_str[0] == delimiter;
}

inline static int count(const char* c_str, const char ch) {
    std::string str(c_str);
    return std::count(str.begin(), str.end(), ch);
}

inline static bool starts_with(const std::string& str, char delimiter) {
    return str.rfind(delimiter, 0) == 0;
}

/* ! \brief fnv-1a hash */
inline int32_t hash(const std::string& str) {
    uint32_t h = 2166136261;
    for (const uint8_t&ch: str) {
        h = h ^ uint32_t(ch);
        h = h * 16777619;
    }
    // for (size_t i = 0; i < str.size(); ++i) {
    //     h = h ^ uint32_t(uint8_t(str[i]));
    //     h = h * 16777619;
    // }
    return h;
}

}  // end of common namespace
}  // endo of w2v namespace

#endif