/// Attributes file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/structures/Attributes.hxx"
#include "test/helper/files/Attributes.hxx"

class AttributesSerializerFileTest : public testing::Test
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

    void verifyTestData(const Helper::AttributesTest & data)
    {
        EXPECT_EQ("Text", data.name);
        EXPECT_EQ(23, data.age);
        EXPECT_DOUBLE_EQ(1.93, data.height);
        EXPECT_EQ(Helper::Day::Tuesday, data.day);
        ASSERT_TRUE(data.optional_age.has_value());
        EXPECT_EQ(18, data.optional_age.value());
        ASSERT_TRUE(data.nickname.has_value());
        EXPECT_EQ("Charlie", data.nickname.value());
        ASSERT_TRUE(data.color.has_value());
        EXPECT_EQ(Helper::Color::Green, data.color.value());
    }

    std::vector<std::string> tempFiles;
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(AttributesSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Attributes.xml";

    const auto base{Helper::loadAttributesElementXML(fileName.string())};
    ASSERT_TRUE(base.has_value());
    verifyTestData(base.value());
}

TEST_F(AttributesSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteAttributes.xml"};
    addTempFile(fileName);

    const Helper::AttributesTest base{
      "Text", 42, 1.75, Helper::Day::Wednesday, std::nullopt, "Goofy", Helper::Color::Red};

    auto result{Helper::saveAttributesElementXML(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadAttributesElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(base.name, loaded->name);
    EXPECT_EQ(base.age, loaded->age);
    EXPECT_DOUBLE_EQ(base.height, loaded->height);
    EXPECT_EQ(base.day, loaded->day);
    EXPECT_FALSE(loaded->optional_age.has_value());
    EXPECT_EQ(base.nickname, loaded->nickname);
    EXPECT_EQ(base.color, loaded->color);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(AttributesSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Attributes.json";

    const auto base{Helper::loadAttributesElementJSON(fileName.string())};
    ASSERT_TRUE(base.has_value());
    verifyTestData(base.value());
}

TEST_F(AttributesSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteAttributes.json"};
    addTempFile(fileName);

    const Helper::AttributesTest base{
      "Text", 42, 1.75, Helper::Day::Wednesday, std::nullopt, "Goofy", Helper::Color::Red};

    auto result{Helper::saveAttributesElementJSON(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadAttributesElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(base.name, loaded->name);
    EXPECT_EQ(base.age, loaded->age);
    EXPECT_DOUBLE_EQ(base.height, loaded->height);
    EXPECT_EQ(base.day, loaded->day);
    EXPECT_FALSE(loaded->optional_age.has_value());
    EXPECT_EQ(base.nickname, loaded->nickname);
    EXPECT_EQ(base.color, loaded->color);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(AttributesSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Attributes.xml";

    const auto base{Helper::loadAttributesElement(fileName.string())};
    ASSERT_TRUE(base.has_value());
    verifyTestData(base.value());
}

TEST_F(AttributesSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Attributes.json";

    const auto base{Helper::loadAttributesElement(fileName.string())};
    ASSERT_TRUE(base.has_value());
    verifyTestData(base.value());
}

TEST_F(AttributesSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteAttributesUnified.xml"};
    addTempFile(fileName);

    const Helper::AttributesTest base{
      "Unified", 99, 2.0, Helper::Day::Friday, 50, "Test", Helper::Color::Blue};

    auto result{Helper::saveAttributesElement(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadAttributesElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(base.name, loaded->name);
    EXPECT_EQ(base.age, loaded->age);
    EXPECT_EQ(base.day, loaded->day);
}

TEST_F(AttributesSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteAttributesUnified.json"};
    addTempFile(fileName);

    const Helper::AttributesTest base{
      "Unified", 99, 2.0, Helper::Day::Friday, 50, "Test", Helper::Color::Blue};

    auto result{Helper::saveAttributesElement(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadAttributesElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    EXPECT_EQ(base.name, loaded->name);
    EXPECT_EQ(base.age, loaded->age);
    EXPECT_EQ(base.day, loaded->day);
}
