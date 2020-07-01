#pragma once
#include <pthread.h>
#include <functional>

class Thread
{
public:
    typedef typename std::function<void()> ThreadFunc;
    Thread(const ThreadFunc&);
    ~Thread();

    void start();
    void join();

private:
    pthread_t threadId_;
    ThreadFunc& func_;
    static void* startThread(void* thread);
    void runInThread();
};

