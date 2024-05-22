#ifndef W2V_APPLICATION_H
#define W2V_APPLICATION_H
#include <w2v/config.h>
#include <w2v/math/matrix.h>
#include <w2v/model.h>
#include <w2v/vocabulary.h>

#include <atomic>

namespace w2v {

class Application {

public:
    Application(int argc, char** argv);
        
    ~Application();

    void run();

private:
    void load_parameters(int argc, char** argv);
    void start();
    void train_thread(int32_t thread_id);


private:
    std::shared_ptr<Config> config_;
    std::shared_ptr<Vocabulary> vocab_;

    std::shared_ptr<Matrix> input_;
    std::shared_ptr<Matrix> output_;

    std::shared_ptr<Model> model_;

    std::atomic<int64_t> total_count_;
};

}  // end of name space w2v
#endif