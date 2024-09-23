#include <gtest/gtest.h>
#include <filesystem>

#include "test/helper/structures/Attributes.hxx"
#include "test/helper/files/AttributesXML.hxx"

TEST(AttributesSerializerTest, Deserialize)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Attributes.xml";

    const auto base{Helper::loadAttributesElement(fileName.string())};
    ASSERT_TRUE(base.has_value());

    EXPECT_EQ("Text", base->name);
    EXPECT_EQ(23, base->age);
    EXPECT_DOUBLE_EQ(1.93, base->height);
    EXPECT_EQ(Helper::Day::Tuesday, base->day);
    ASSERT_TRUE(base->optional_age.has_value());
    EXPECT_EQ(18, base->optional_age.value());
    ASSERT_TRUE(base->nickname.has_value());
    EXPECT_EQ("Charlie", base->nickname.value());
    ASSERT_TRUE(base->color.has_value());
    EXPECT_EQ(Helper::Color::Green, base->color.value());
}

TEST(AttributesSerializerTest, Serialize)
{
    const Helper::AttributesTest base{
      "Text", 42, 1.75, Helper::Day::Wednesday, std::nullopt, "Goofy", Helper::Color::Red};

    const std::string fileName{"TestWrite.xml"};
    std::remove(fileName.c_str());
    auto result{Helper::saveAttributesElement(base, fileName)};

    EXPECT_EQ(0, result);

    const auto loadedBase{Helper::loadAttributesElement(fileName)};
    ASSERT_TRUE(loadedBase.has_value());

    EXPECT_EQ(base.name, loadedBase->name);
    EXPECT_EQ(base.age, loadedBase->age);
    EXPECT_DOUBLE_EQ(base.height, loadedBase->height);
    EXPECT_EQ(base.day, loadedBase->day);
    EXPECT_FALSE(loadedBase->optional_age.has_value());
    EXPECT_EQ(base.nickname, loadedBase->nickname);
    EXPECT_EQ(base.color, loadedBase->color);

    std::remove(fileName.c_str());
}
