/// EnumElement file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/FileManipulation.hxx"
#include "test/helper/files/EnumElement.hxx"
#include "test/helper/structures/StructureEnum.hxx"

class EnumSerializerFileTest : public testing::Test
{
protected:
    void TearDown() override
    {
        for(const auto & file : tempFiles)
        {
            std::remove(file.c_str());
        }
    }

    void addTempFile(const std::string & name)
    {
        tempFiles.push_back(name);
    }

    std::vector<std::string> tempFiles;
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElement.xml";

    const auto element{Helper::loadEnumElementXML(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_TRUE(element->color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element->color.value());
}

TEST_F(EnumSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteEnum.xml"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;
    enumEl.color = Helper::Color::Green;

    const auto result{Helper::saveEnumElementXML(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Friday, loaded->day);
    EXPECT_TRUE(loaded->color.has_value());
    EXPECT_EQ(Helper::Color::Green, loaded->color.value());
}

TEST_F(EnumSerializerFileTest, ReadOptionalMissingXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElementMissing.xml";

    const auto element{Helper::loadEnumElementXML(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_FALSE(element->color.has_value());
}

TEST_F(EnumSerializerFileTest, WriteAndReadOptionalMissingXML)
{
    const std::string fileName{"TestWriteEnumMissing.xml"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;

    const auto result{Helper::saveEnumElementXML(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Friday, loaded->day);
    EXPECT_FALSE(loaded->color.has_value());
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElement.json";

    const auto element{Helper::loadEnumElementJSON(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_TRUE(element->color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element->color.value());
}

TEST_F(EnumSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteEnum.json"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;
    enumEl.color = Helper::Color::Green;

    const auto result{Helper::saveEnumElementJSON(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Friday, loaded->day);
    EXPECT_TRUE(loaded->color.has_value());
    EXPECT_EQ(Helper::Color::Green, loaded->color.value());
}

TEST_F(EnumSerializerFileTest, ReadOptionalMissingJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElementMissing.json";

    const auto element{Helper::loadEnumElementJSON(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_FALSE(element->color.has_value());
}

TEST_F(EnumSerializerFileTest, WriteAndReadOptionalMissingJSON)
{
    const std::string fileName{"TestWriteEnumMissing.json"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Friday;

    const auto result{Helper::saveEnumElementJSON(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Friday, loaded->day);
    EXPECT_FALSE(loaded->color.has_value());
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElement.xml";

    const auto element{Helper::loadEnumElement(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_TRUE(element->color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element->color.value());
}

TEST_F(EnumSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "EnumElement.json";

    const auto element{Helper::loadEnumElement(fileName.string())};
    ASSERT_TRUE(element.has_value());

    EXPECT_EQ(Helper::Day::Monday, element->day);
    EXPECT_TRUE(element->color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element->color.value());
}

TEST_F(EnumSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteEnumUnified.xml"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Wednesday;
    enumEl.color = Helper::Color::Red;

    const auto result{Helper::saveEnumElement(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Wednesday, loaded->day);
    EXPECT_TRUE(loaded->color.has_value());
    EXPECT_EQ(Helper::Color::Red, loaded->color.value());
}

TEST_F(EnumSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteEnumUnified.json"};
    addTempFile(fileName);

    Helper::EnumElement enumEl;
    enumEl.day = Helper::Day::Wednesday;
    enumEl.color = Helper::Color::Red;

    const auto result{Helper::saveEnumElement(enumEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(Helper::Day::Wednesday, loaded->day);
    EXPECT_TRUE(loaded->color.has_value());
    EXPECT_EQ(Helper::Color::Red, loaded->color.value());
}
