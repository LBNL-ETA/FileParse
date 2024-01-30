#include <gtest/gtest.h>

#include "test/helper/FileManipulation.hxx"

#include "test/helper/files/EnumElementXML.hxx"
#include "test/helper/structures/StructureEnum.hxx"

class EnumSerializerXMLTest : public testing::Test
{};

TEST_F(EnumSerializerXMLTest, TestReading)
{
    const std::string fileContent{Helper::testEnumDatabase()};
    const std::string fileName{"TestRead.xml"};

    std::remove(fileName.c_str());
    File::createFileFromString(fileName, fileContent);

    Helper::EnumElement element{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(Helper::Day::Monday, element.day);
    EXPECT_EQ(true, element.color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element.color.value());

    std::remove(fileName.c_str());
}

TEST_F(EnumSerializerXMLTest, TestWriting)
{
    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;
    enumEl.color = Helper::Color::Green;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumElement(enumEl, fileName)};

    EXPECT_EQ(0, result);

    const auto loadedEnum{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(Helper::Day::Friday, loadedEnum.day);
    EXPECT_EQ(true, loadedEnum.color.has_value());
    EXPECT_EQ(Helper::Color::Green, loadedEnum.color.value());

    std::remove(fileName.c_str());
}

TEST_F(EnumSerializerXMLTest, TestReadingOptionalMissing)
{
    const std::string fileContent{Helper::testEnumDatabaseOptionalMissing()};
    const std::string fileName{"TestRead.xml"};

    std::remove(fileName.c_str());
    File::createFileFromString(fileName, fileContent);

    Helper::EnumElement element{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(static_cast<int>(Helper::Day::Monday), static_cast<int>(element.day));
    EXPECT_EQ(false, element.color.has_value());

    std::remove(fileName.c_str());
}

TEST_F(EnumSerializerXMLTest, TestWritingOptionalMissing)
{
    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumElement(enumEl, fileName)};

    EXPECT_EQ(0, result);

    const auto loadedEnum{Helper::loadEnumElement(fileName)};

    EXPECT_EQ(static_cast<int>(Helper::Day::Friday), static_cast<int>(loadedEnum.day));
    EXPECT_EQ(false, loadedEnum.color.has_value());

    std::remove(fileName.c_str());
}