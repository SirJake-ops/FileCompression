//
// Created by jake2 on 12/27/2024.
//

/*
 * TODO: File Compression
 * TODO: File Decompression
 * TODO: Archive Content Viewer
 * TODO: File Deletion from Archive
 * TODO: File Addition to Archive
 *
 * File Compression Implement functionality to compress files into various formats (e.g., ZIP, TAR).
 * Provide a user interface for selecting files and choosing compression options.
 * File Decompression
 * Implement functionality to decompress files from various formats.
 * Provide a user interface for selecting compressed files and choosing destination folders.
 * Archive Content Viewer
 * Implement functionality to view the contents of a compressed file without decompressing it.
 * Display file names, sizes, and types in a user-friendly interface.
 * File Deletion from Archive
 * Implement functionality to delete files from a compressed archive.
 * Provide a user interface for selecting files to delete and confirming the action.
 * File Addition to Archive
 * Implement functionality to add files to an existing compressed archive.
 * Provide a user interface for selecting files to add and updating the archive.
 * */

#ifndef FILECOMPRESSIONPROJECT_LOADDATA_H
#define FILECOMPRESSIONPROJECT_LOADDATA_H


#include <string>
#include <utility>
#include <cstdint>
#include <vector>
#include <memory>
#include "configs/OSConfig.h"
#include "FileManipulationHelperMethod.h"

class LoadData : FileManipulationHelperMethod {
public:
    LoadData(): osName_(OS_NAME){}

    explicit LoadData(const std::string &filename, const std::string &filePath) : filename_(
        std::move(filename)), filePath_(filePath), osName_(OS_NAME) {
    }

    ~LoadData() override = default;

    void writeCompressedFile(const std::string &fileName, const std::string &filePath) override;

    std::vector<uint8_t> downloadCompressedFile(const std::string &fileName, const std::string &filePath) override;



    std::string getFileName() const {
        return this->filename_;
    }

    std::string getFilePath() const {
        return this->filePath_;
    }

private:
    std::string osName_;
    std::string filename_;
    std::string filePath_;
    std::mutex mutex_;
};

#endif //FILECOMPRESSIONPROJECT_LOADDATA_H
