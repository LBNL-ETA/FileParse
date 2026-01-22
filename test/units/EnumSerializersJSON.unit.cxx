#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/FileManipulation.hxx"

#include "test/helper/files/EnumElement.hxx"
#include "test/helper/structures/StructureEnum.hxx"

class EnumSerializerJSONTest : public testing::Test
{};

TEST_F(EnumSerializerJSONTest, TestReading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElement.json";

    const auto element{Helper::loadEnumElementJSON(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_EQ(true, element->color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element->color.value());
}

TEST_F(EnumSerializerJSONTest, TestWriting)
{
    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;
    enumEl.color = Helper::Color::Green;

    const std::string fileName{"TestWrite.json"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumElementJSON(enumEl, fileName)};

    EXPECT_EQ(0, result);

    const auto loadedEnum{Helper::loadEnumElementJSON(fileName)};
    ASSERT_TRUE(loadedEnum.has_value());

    EXPECT_EQ(Helper::Day::Friday, loadedEnum->day);
    EXPECT_EQ(true, loadedEnum->color.has_value());
    EXPECT_EQ(Helper::Color::Green, loadedEnum->color.value());

    std::remove(fileName.c_str());
}

TEST_F(EnumSerializerJSONTest, TestReadingOptionalMissing)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElementMissing.json";

    const auto element{Helper::loadEnumElementJSON(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(static_cast<int>(Helper::Day::Monday), static_cast<int>(element->day));
    EXPECT_EQ(false, element->color.has_value());
}

TEST_F(EnumSerializerJSONTest, TestWritingOptionalMissing)
{
    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumElementJSON(enumEl, fileName)};

    EXPECT_EQ(0, result);

    const auto loadedEnum{Helper::loadEnumElementJSON(fileName)};
    ASSERT_TRUE(loadedEnum.has_value());

    EXPECT_EQ(static_cast<int>(Helper::Day::Friday), static_cast<int>(loadedEnum->day));
    EXPECT_EQ(false, loadedEnum->color.has_value());

    std::remove(fileName.c_str());
}
