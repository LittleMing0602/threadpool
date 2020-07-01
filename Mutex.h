#pragma once

#include <pthread.h>
#include <assert.h>

class MutexLock
{
public:
    MutexLock() {
        int ret = pthread_mutex_init(&_mutex, NULL);
        assert(ret == 0);
    }
    ~MutexLock() {
        int ret = pthread_mutex_destroy(&_mutex);
        assert(ret == 0);
    }

    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }

private:
    pthread_mutex_t _mutex;

};

//RAII
class MutexLockGuard{
public:
    explicit MutexLockGuard(MutexLock& mutex):mutex_(mutex){
        mutex_.lock();
    }

    ~MutexLockGuard(){
        mutex_.unlock();
    }

private:
    MutexLock& mutex_;

};


//禁止这样的使用方法 MutexLockGuard(mutex);
#define MutexLockGuard(x) error "missing object name"
