//
// Created by Jacob Pagan on 1/12/2025.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <future>


#ifndef FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H
#define FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H

struct Chunk {
    std::string filename_;
    std::size_t start_;
    std::size_t end_;
};

class FileManipulationHelperMethod {
public:
    virtual ~FileManipulationHelperMethod() = default;

    FileManipulationHelperMethod() = default;

    virtual void writeCompressedFile(const std::string &fileName, const std::string &filePath) = 0;

    virtual std::vector<std::uint8_t> readCompressedFile(const std::string &fileName, const std::string &filePath) = 0;

    virtual void processFileChunk(const Chunk& chunk) = 0;

    virtual std::vector<Chunk> createChunks(const std::size_t fileSize) = 0;
};


#endif //FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H
