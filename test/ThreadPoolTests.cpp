//
// Created by Jacob Pagan on 1/19/25.
//


#include <fstream>
#include <gmock/gmock-function-mocker.h>
#include <gtest/gtest.h>
#include "ThreadFunctionality/ThreadPool.h"

class MockThreadPool final : public ThreadPoolInterface {
public:
    MOCK_METHOD(int, getThreadCount, (), (const, override));
    MOCK_METHOD(int, getQueueCount, (), (const, override));
    MOCK_METHOD(void, Start, (), (override));
    MOCK_METHOD(void, QueueJob, (const std::function<void()> &job), (override));
    MOCK_METHOD(void, Stop, (), (override));
    MOCK_METHOD(bool, busy, (), (override));
    MOCK_METHOD(bool, getShouldTerminate, (), (const, override));
    MOCK_METHOD(void, processFileChunk, (std::vector<std::future<void>>& futures, const std::vector<Chunk>& chunks),
                (override));
    MOCK_METHOD(std::vector<Chunk>, createChunks, (const std::string& fileName, const std::size_t fileSize),
                (override));
    MOCK_METHOD(void, processChunk, (std::ifstream& file, const Chunk& chunk), (override));


    template<typename F, typename... Args>
    auto enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        std::promise<return_type> promise;
        auto future = promise.get_future();
        promise.set_value(f(std::forward<Args>(args)...));
        return future;
    }
};

TEST(ThreadPoolStartTest, BasicAssertions) {
    const uint32_t machine_thread_count = std::thread::hardware_concurrency() / 2;

    MockThreadPool mock_thread_pool;

    EXPECT_CALL(mock_thread_pool, Start()).Times(1);
    EXPECT_CALL(mock_thread_pool, getThreadCount()).WillOnce(testing::Return(12));

    mock_thread_pool.Start();
    const int result = mock_thread_pool.getThreadCount();

    EXPECT_EQ(result, machine_thread_count);
}

TEST(ThreadPoolQueueJobTest, BasicAssertions) {
    MockThreadPool mock_thread_pool;
    const std::function<void()> job = []() {
    };

    EXPECT_CALL(mock_thread_pool, QueueJob(testing::_)).Times(1);
    EXPECT_CALL(mock_thread_pool, getQueueCount()).WillOnce(testing::Return(1));

    mock_thread_pool.QueueJob(job);

    const int result = mock_thread_pool.getQueueCount();

    EXPECT_EQ(result, 1);
}

TEST(ThreadPoolStopTest, BasicAssertions) {
    MockThreadPool mock_thread_pool;

    EXPECT_CALL(mock_thread_pool, Stop()).Times(1);
    EXPECT_CALL(mock_thread_pool, getThreadCount()).WillOnce(testing::Return(0));

    mock_thread_pool.Stop();
    const int result = mock_thread_pool.getThreadCount();

    EXPECT_EQ(result, 0);
}


TEST(ThreadPoolProcessFileChunkTest, BasicAssertions) {
    MockThreadPool mock_thread_pool;
    std::vector<std::future<void> > futures;
    std::vector<Chunk> chunks = {
        {"test1.dat", 0, 1024},
        {"test2.dat", 1024, 2048},
        {"test3.dat", 2048, 3072},
    };

    EXPECT_CALL(mock_thread_pool, processChunk(testing::_, testing::_)).Times(chunks.size());

    for (const auto &chunk: chunks) {
        futures.push_back(std::async(std::launch::async, [&mock_thread_pool, &chunk]() {
            std::ifstream file(chunk.filename_);
            mock_thread_pool.processChunk(file, chunk);
        }));
    }

    for (auto &future: futures) {
        future.wait();
    }
}

TEST(ThreadPoolCreateChunksTest, BasicAssertions) {
    MockThreadPool mock_thread_pool;
    const int threadCount = std::thread::hardware_concurrency() / 2;
    constexpr std::size_t fileSize = 1024 * 1024;
    const std::size_t chunkSize = fileSize / threadCount;

    std::vector<Chunk> chunks;

    for (std::size_t start = 0; start < fileSize; start += chunkSize) {
        std::size_t end = std::min(start + chunkSize, fileSize);
        chunks.push_back({"testFile.dat", start, end});
    }
    EXPECT_CALL(mock_thread_pool, createChunks("testFile.dat", fileSize)).WillOnce(testing::Return(chunks));

    auto result = mock_thread_pool.createChunks("testFile.dat", fileSize);

    const int expectedSize = chunks.size();

    EXPECT_EQ(result.size(), expectedSize);
}

TEST(ThreadPoolEnqueueTest, BasicAssertions) {
    MockThreadPool mock_thread_pool;

    auto job = []() { return 42; };

    auto future = mock_thread_pool.enqueue(job);

    const int result = future.get();

    EXPECT_EQ(result, 42);
}
