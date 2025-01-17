//
// Created by Jacob Pagan on 1/10/2025.
//


#include <gtest/gtest.h>
#include "../FileManipulation/FileData.h"


TEST(FileDataTest, BasicAssertions) {
    std::vector<uint8_t> fakeData;
    std::string fakeFileName{"Fake Name"};
    std::unique_ptr<FileData> fileData = std::make_unique<FileData>(fakeFileName, fakeData);

    ASSERT_EQ(fileData->getFileName(), fakeFileName);
    ASSERT_EQ(fileData->getFileData(), fakeData);

    ASSERT_NE(fileData->getFileProps(), nullptr);
}