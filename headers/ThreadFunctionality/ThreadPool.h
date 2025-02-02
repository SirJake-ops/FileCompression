//
// Created by Jacob Pagan on 1/17/25.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include "ThreadFunctionality/ThreadPoolInterface.h"

template<typename T>
concept functionVoid = std::same_as<T, std::function<void()>>;

template<functionVoid Func>
class ThreadPool final : public ThreadPoolInterface {
public:
    ~ThreadPool() override;

    void Start() override;

    void QueueJob(const std::function<void()> &job) override;

    void Stop() override;

    bool busy() override;

    int getThreadCount() const override;

    int getQueueCount() const override;

    bool getShouldTerminate() const override;

    // void processFileChunk(std::vector<std::future<void()> > &futures, const std::vector<Chunk> &chunks) override;
    //
    // std::vector<Chunk> createChunks(const std::string &fileName, const std::size_t fileSize) override;
    //
    // template<typename F, typename... Args>
    // auto enqueue(F &&f, Args &&... args) -> std::future<std::result_of_t<F(Args...)> >;
    //
    // void processChunk(std::ifstream& file, const Chunk& chunk) override;

private:
    void ThreadLoop();

    bool should_terminate = false;
    std::mutex queueMutex_;
    std::condition_variable mutexCondition_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()> > jobs_;
};

#include "ThreadPool.tpp"

#endif //THREADPOOL_H
