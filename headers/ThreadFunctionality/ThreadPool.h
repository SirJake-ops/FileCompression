//
// Created by Jacob Pagan on 1/17/25.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

/**
 * TODO: This is an example class that I found online that I am planning on using for this functionality. \
 * This is more than likely not the final class I will be using, but a very nice skeleton.
 *
 */
class ThreadPool {
public:
    void Start();

    void QueueJob(const std::function<void()> &job);

    void Stop();

    bool busy();

private:
    void ThreadLoop();

    bool should_terminate = false;
    std::mutex queueMutex_;
    std::condition_variable mutexCondition_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()> > jobs_;
};


#endif //THREADPOOL_H
