//
// Created by Jacob Pagan on 1/17/25.
//

#include "ThreadPool.h"

void ThreadPool::Start() {
    const uint32_t numberOfThreads = std::thread::hardware_concurrency() / 2;

    for (uint32_t i = 0; i < numberOfThreads; ++i) {
        threads_.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
    }
}

void ThreadPool::ThreadLoop() {
    while (true) {
        std::function<void()> job;
        {
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
