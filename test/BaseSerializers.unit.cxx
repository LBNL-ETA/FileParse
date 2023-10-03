#include <gtest/gtest.h>

#include "helper/TestXML.hxx"
#include "helper/TestStructures.hxx"

#include "helper/FileManipulation.hxx"
#include "helper/TestSerializers.hxx"

class BaserSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(BaserSerializerTest, TestReadingBaseElement)
{
    const std::string fileContent{Helper::testDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    Helper::BaseElement base{Helper::loadBaseElement(fileName)};

    EXPECT_EQ("TestText", base.text);

    std::remove(fileName.c_str());
}