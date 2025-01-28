//
// Created by Jacob Pagan on 12/27/2024.
//


#include "LoadData.h"
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

void LoadData::writeCompressedFile(const std::string &fileName, const std::string &filePath) {
    try {
        std::filesystem::path fileDirectory = std::filesystem::current_path();
        std::string completeFilePath;
        if (osName_ == "Windows") {
            completeFilePath = filePath + "\\" + fileName;
        } else {
            completeFilePath = filePath + "/" + fileName;
        }

        std::ifstream inFile(completeFilePath, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::runtime_error("File could not be opened or does not exist");
        }

        std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

        inFile.close();

        std::string tempFile;
        if (osName_ == "Windows") {
            tempFile = filePath + "\\temp_" + fileName + ".gz";
        } else {
            tempFile = filePath + "/temp_" + fileName + ".gz";
        }

        std::ofstream outFile(tempFile, std::ios::binary);

        if (!outFile) {
            std::cerr << "File to write is not available " << tempFile << std::endl;
        }

        boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
        out.push(boost::iostreams::gzip_compressor());
        out.push(outFile);

        std::ostream compressedOut(&out);

        compressedOut.write(reinterpret_cast<const char *>(fileData.data()), fileData.size());
        boost::iostreams::close(out);
        outFile.close();

        std::cout << "Compression is finished" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

std::vector<uint8_t> LoadData::readCompressedFile(const std::string &fileName, const std::string &filePath) {
    try {
        std::string completeFilePath;
        if (osName_ == "Windows") {
            completeFilePath = filePath + "\\" + fileName;
        } else {
            completeFilePath = filePath + "/" + fileName;
        }
        std::ifstream inFile(completeFilePath, std::ios::binary);

        if (!inFile.is_open()) {
            throw std::runtime_error("File could not be open or does not exist");
        }

        boost::iostreams::filtering_streambuf<boost::iostreams::input> input;
        input.push(boost::iostreams::gzip_decompressor());
        input.push(inFile);

        std::vector<std::uint8_t> decompressedData((std::istreambuf_iterator<char>(inFile)),
                                                   std::istreambuf_iterator<char>());

        inFile.close();

        return decompressedData;
    } catch (const std::exception &e) {
        std::cerr << "File not available: " << fileName << e.what() << std::endl;
    }
    return {};
}
