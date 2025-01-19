//
// Created by Jacob Pagan on 1/9/2025.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FileManipulation/LoadData.h"


class LoadDataInterface {
public:
    virtual std::vector<uint8_t> getFileData(const std::string& fileName, const std::string& filePath) = 0;
};


class MockLoadData: public LoadDataInterface {
public:
    MOCK_METHOD(std::vector<uint8_t>, getFileData, (const std::string& fileName, const std::string& filePath), (override));
};

TEST(LoadDataTest, BasicAssertions) {
    std::unique_ptr<LoadData> loadTestData = std::make_unique<LoadData>("Test", "root/Test");

    EXPECT_EQ(loadTestData->getFileName(), "Test");
    EXPECT_EQ(loadTestData->getFilePath(), "root/Test");
}


TEST(fileWriteAndRead, BasicAssertions) {
    const std::string fileName = "Test";
    const std::string filePath = "root/Test";

    MockLoadData mockLoadData;
    EXPECT_CALL(mockLoadData, getFileData(fileName, filePath)).WillOnce(testing::Return(std::vector<uint8_t>()));

    std::vector<uint8_t> result = mockLoadData.getFileData(fileName, filePath);


    EXPECT_EQ(result, std::vector<uint8_t>());

}