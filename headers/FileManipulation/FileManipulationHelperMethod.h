//
// Created by Jacob Pagan on 1/12/2025.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>


#ifndef FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H
#define FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H


class FileManipulationHelperMethod {
public:
    virtual ~FileManipulationHelperMethod() = default;
    FileManipulationHelperMethod() = default;

    virtual void writeCompressedFile(const std::string &fileName, const std::string &filePath) = 0;

    virtual std::vector<std::uint8_t> readCompressedFile(const std::string &fileName, const std::string &filePath) = 0;
};


#endif //FILECOMPRESSIONPROJECT_FILEMANIPULATIONHELPERMETHOD_H
