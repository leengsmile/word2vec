#include <w2v/utils/stream.h>
#include <ios>

namespace w2v {
namespace common {

int64_t size(std::ifstream& ifs) {
    ifs.seekg(std::streampos(0), std::ios::end);
    return ifs.tellg();
}

void seek(std::ifstream& ifs, int64_t pos) {
    ifs.clear();
    ifs.seekg(std::streampos(pos));
}

}  // end of stream
}  // end of w2v