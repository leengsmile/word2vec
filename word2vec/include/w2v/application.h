#ifndef W2V_APPLICATION_H
#define W2V_APPLICATION_H
#include <w2v/config.h>
#include <w2v/vocabulary.h>

namespace w2v {

class Application {

public:
    Application(int argc, char** argv);
        
    ~Application();

    void run();

private:
    void load_parameters(int argc, char** argv);

private:
    Config config;
    Vocabulary vocab;
};

}  // end of name space w2v
#endif