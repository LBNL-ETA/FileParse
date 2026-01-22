#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/SetElement.hxx"
#include "test/helper/structures/StructureSet.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(SetSerializerXMLTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.xml";

    const auto setEl{Helper::loadSetElementDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST(SetSerializerXMLTest, Writing)
{
    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDoubleXML(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadSetElementDoubleXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values, loadedVector->values, tolerance);

    std::remove(fileName.c_str());
}

TEST(SetSerializerXMLTest, OptionalReading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableOptional.xml";

    const auto setEl{Helper::loadSetElementOptionalDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    EXPECT_EQ(true, setEl->values.has_value());

    const std::set<double> correct{43.215483, 76.842907, 12.689342};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl->values.value(), tolerance);
}

TEST(SetSerializerXMLTest, OptionalWriting)
{
    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementOptionalDoubleXML(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementOptionalDoubleXML(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    EXPECT_EQ(true, loadedSet->values.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values.value(), loadedSet->values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST(SetSerializerXMLTest, ReadingEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEmpty.xml";

    const auto setEl{Helper::loadSetElementDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    EXPECT_EQ(0u, setEl->values.size());
}

TEST(SetSerializerXMLTest, WritingEmpty)
{
    Helper::SetElementDouble setEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDoubleXML(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementDoubleXML(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    EXPECT_EQ(setEl.values.size(), loadedSet->values.size());

    std::remove(fileName.c_str());
}

TEST(SetSerializerXMLTest, ReadingEnum)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.xml";

    const auto setEl{Helper::loadSetElementEnumXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}

TEST(SetSerializerXMLTest, WritingEnum)
{
    Helper::SetElementEnum setEl;
    using Helper::Day;
    setEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Sunday};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementEnumXML(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementEnumXML(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    Helper::checkSetEquality(setEl.days, loadedSet->days, Helper::toDayString);

    std::remove(fileName.c_str());
}