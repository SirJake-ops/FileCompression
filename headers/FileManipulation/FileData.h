//
// Created by Jacob Pagan on 12/26/2024.
//

#ifndef FILECOMPRESSIONPROJECT_FILEDATA_H
#define FILECOMPRESSIONPROJECT_FILEDATA_H


#include <string>
#include <cstdint>
#include <utility>
#include <vector>



struct FileProps {
    std::string filename_;
    std::vector<std::uint8_t> data_;
};

class FileData {
public:
    explicit FileData(const std::string& fileName, const std::vector<std::uint8_t>& data);


    FileProps* getFileProps() {
        return &fileProps_;
    }

    const std::string getFileName()const {
        return this->fileProps_.filename_;
    }

    std::vector<uint8_t> getFileData()const {
        return this->fileProps_.data_;
    }

private:
    FileProps fileProps_;
};


#endif //FILECOMPRESSIONPROJECT_FILEDATA_H
