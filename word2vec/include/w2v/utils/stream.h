#ifndef W2V_STREAM_H
#define W2V_STREAM_H

#include <fstream>

namespace w2v {
namespace common {

int64_t size(std::ifstream& ifs);

void seek(std::ifstream& ifs, int64_t pos);

}
}
#endif