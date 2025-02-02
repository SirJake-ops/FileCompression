//
// Created by Jacob Pagan on 1/23/25.
//

#ifndef THREADPOOLINTERFACE_H
#define THREADPOOLINTERFACE_H

struct Chunk {
    std::string filename_;
    std::size_t start_;
    std::size_t end_;
};

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

    // virtual void processFileChunk(std::vector<std::future<void()>>& futures, const std::vector<Chunk>& chunks) = 0;
    //
    // virtual std::vector<Chunk> createChunks(const std::string &fileName, const std::size_t fileSize) = 0;
    //
    // virtual void processChunk(std::ifstream& file, const Chunk& chunk) = 0;
};


#endif //THREADPOOLINTERFACE_H
