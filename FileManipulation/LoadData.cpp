//
// Created by Jacob Pagan on 12/27/2024.
//


#include "LoadData.h"
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

//std::vector<std::uint8_t> LoadData::writeFile(const std::string &fileName, const std::string &fileDirectory) {
//    try {
//        const std::string completeFilePath = fileDirectory + "\\" + fileName;
//        std::ifstream inFile(completeFilePath, std::ios::binary);
//
//
//        if (!inFile.is_open()) {
//            throw std::runtime_error("File could not be opened or does not exist. " + fileName);
//        }
//
//        std::vector<std::uint8_t> readData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
//        inFile.close();
//
//        return readData;
//    } catch (const std::exception &e) {
//        std::cerr << "Exception caught: " << e.what() << std::endl;
//    }
//    return std::vector<std::uint8_t>();
//}

//void LoadData::readFile(const std::string &fileName, const std::string &filePath) {
//    try {
//        //Everthing until the outfile.write needs to be in new method.
//        char buffer[1024];
//        std::filesystem::path fileDirectory = std::filesystem::current_path();
//        std::string tempFile = filePath + "\\temp_" + fileName;
//        std::vector<std::uint8_t> binaryData = writeFile(fileName, filePath);
//
//
//        std::ofstream outFile(tempFile, std::ios::binary);
//
//
//
//        if (!outFile.is_open()) {
//            throw std::runtime_error("File could not be opened or does not exist. " + fileName);
//        }
//
//        outFile.write(reinterpret_cast<const char *>(binaryData.data()), binaryData.size());
//
//        outFile.close();
//
//    } catch (const std::exception &e) {
//        std::cerr << "Exception caught: " << e.what() << std::endl;
//    }
//}

void LoadData::writeCompressedFile(const std::string &fileName, const std::string& filePath) {
    try {
        char buffer[1024];
        std::filesystem::path fileDirectory = std::filesystem::current_path();
        std::string tempFile = filePath + "\\temp_" + fileName;

        std::vector<std::uint8_t> binaryData = readCompressedFile(fileName, filePath);
        std::ofstream outFile(tempFile, std::ios::binary);

        if (!outFile) {
            std::cerr << "File to write is not available" << fileName << std::endl;
            return;
        }

        boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
        out.push(boost::iostreams::zlib_compressor());
        out.push(outFile);

        std::ostream compressedOut(&out);

        compressedOut.write(reinterpret_cast<const char *>(binaryData.data()), binaryData.size());
        outFile.close();

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

std::vector<uint8_t> LoadData::readCompressedFile(const std::string &fileName, const std::string &filePath) {
    try {
        const std::string completeFilePath = filePath + "\\" + fileName;
        std::ifstream inFile(completeFilePath, std::ios::binary);

        if (!inFile.is_open()) {
            throw std::runtime_error("File could not be open or does not exist");
        }

        boost::iostreams::filtering_streambuf<boost::iostreams::input> input;
        input.push(boost::iostreams::gzip_decompressor());
        input.push(inFile);

        std::vector<std::uint8_t> decompressedData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

        inFile.close();

        return decompressedData;


    } catch (const std::exception& e) {
        std::cerr << "File not available: " << fileName << e.what() << std::endl;
    }
    return {};
}

