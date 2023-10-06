#include <gtest/gtest.h>

#include "helper/TestEnumElementXML.hxx"
#include "helper/TestStructures.hxx"

#include "helper/FileManipulation.hxx"
#include "test/helper/serializers/TestBaseElementSerializers.hxx"

class EnumSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(EnumSerializerTest, TestReading)
{
    const std::string fileContent{Helper::testEnumDatabase()};
    const std::string fileName{"TestRead.xml"};

    std::remove(fileName.c_str());
    File::createFileFromString(fileName, fileContent);

    Helper::EnumElement element{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(Helper::Day::Monday, element.day);

    std::remove(fileName.c_str());
}

TEST_F(EnumSerializerTest, TestWriting)
{
    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
    std::remove(fileName.c_str());

    Helper::saveEnumElement(enumEl, fileName);

    const auto loadedEnum{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(Helper::Day::Friday, loadedEnum.day);
    EXPECT_EQ(false, loadedEnum.color.has_value());

    std::remove(fileName.c_str());
}