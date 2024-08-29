#include <gtest/gtest.h>

#include "test/helper/structures/Attributes.hxx"

#include "test/helper/files/AttributesXML.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(AttributesSerializerTest, Deserialize)
{
    const std::string fileContent{Helper::testAttributesDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    Helper::AttributesTest base{Helper::loadAttributesElement(fileName)};

    EXPECT_EQ("Text", base.name);
    EXPECT_EQ(23, base.age);
    EXPECT_DOUBLE_EQ(1.93, base.height);
    EXPECT_EQ(Helper::Day::Tuesday, base.day);

    std::remove(fileName.c_str());
}

TEST(AttributesSerializerTest, Serialize)
{
    const Helper::AttributesTest base{"Text", 42, 1.75, Helper::Day::Wednesday};

    const std::string fileName{"TestWrite.xml"};
    std::remove(fileName.c_str());
    auto result{Helper::saveAttributesElement(base, fileName)};

    EXPECT_EQ(0, result);

    Helper::AttributesTest loadedBase{Helper::loadAttributesElement(fileName)};

    EXPECT_EQ(base.name, loadedBase.name);
    EXPECT_EQ(base.age, loadedBase.age);
    EXPECT_DOUBLE_EQ(base.height, loadedBase.height);
    EXPECT_EQ(base.day, loadedBase.day);

    std::remove(fileName.c_str());
}
