//
// Created by Jacob Pagan on 1/17/25.
//

#include "ThreadPool.h"

template<typename Func>
ThreadPool<Func>::~ThreadPool() = default;


template<typename Func>
void ThreadPool<Func>::Start() {
    const uint32_t numberOfThreads = std::thread::hardware_concurrency() / 2;

    for (uint32_t i = 0; i < numberOfThreads; ++i) {
        threads_.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
    }
}

template<typename Func>
void ThreadPool<Func>::QueueJob(const std::function<void()> &job) { {
        std::unique_lock<std::mutex> lock(queueMutex_);
        jobs_.push(job);
    }
    mutexCondition_.notify_one();
}

template<typename Func>
void ThreadPool<Func>::Stop() { {
        std::unique_lock<std::mutex> lock(queueMutex_);
        should_terminate = true;
    }
    mutexCondition_.notify_all();
    for (auto &activeThread: threads_) {
        activeThread.join();
    }
    threads_.clear();
}

template<typename Func>
bool ThreadPool<Func>::busy() {
    bool poolBusy; {
        std::unique_lock<std::mutex> lock(queueMutex_);
        poolBusy = !jobs_.empty();
    }
    return poolBusy;
}

template<typename Func>
int ThreadPool<Func>::getThreadCount() const {
    return this->threads_.size();
}

template<typename Func>
int ThreadPool<Func>::getQueueCount() const {
    return this->jobs_.size();
}

template<typename Func>
bool ThreadPool<Func>::getShouldTerminate() const {
    return this->should_terminate;
}


template<typename Func>
void ThreadPool<Func>::ThreadLoop() {
    while (true) {
        std::function<void()> job; {
            std::unique_lock<std::mutex> lock(queueMutex_);
            mutexCondition_.wait(lock, [this] {
                return !jobs_.empty() || should_terminate;
            });

            if (should_terminate) {
                return;
            }

            job = jobs_.front();
            jobs_.pop();
        }

        job();
    }
}
