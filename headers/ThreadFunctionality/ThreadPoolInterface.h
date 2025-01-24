//
// Created by Jacob Pagan on 1/23/25.
//

#ifndef THREADPOOLINTERFACE_H
#define THREADPOOLINTERFACE_H


class ThreadPoolInterface {
public:
    virtual ~ThreadPoolInterface() = default;

    virtual void Start() = 0;

    virtual void QueueJob(const std::function<void()> &job) = 0;

    virtual void Stop() = 0;

    virtual bool busy() = 0;

    virtual int getThreadCount() const = 0;

    virtual int getQueueCount() const = 0;

    virtual bool getShouldTerminate() const = 0;
};


#endif //THREADPOOLINTERFACE_H
