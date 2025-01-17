//
// Created by jake2 on 12/26/2024.
//

#include "FileData.h"

FileData::FileData(const std::string &fileName, const std::vector<std::uint8_t> &data) {
    this->fileProps_.filename_ = fileName;
    this->fileProps_.data_ = data;
}
