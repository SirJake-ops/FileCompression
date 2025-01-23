//
// Created by Jacob Pagan on 1/19/25.
//


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
