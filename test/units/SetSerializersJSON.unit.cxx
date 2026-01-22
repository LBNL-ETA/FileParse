#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/SetElementJSON.hxx"
#include "test/helper/structures/StructureSet.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(SetSerializerJSONTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.json";

    const auto setEl{Helper::loadSetElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST(SetSerializerJSONTest, Writing)
{
    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDoubleJSON(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadSetElementDoubleJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values, loadedVector->values, tolerance);

    std::remove(fileName.c_str());
}

TEST(SetSerializerJSONTest, OptionalReading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableOptional.json";

    const auto setEl{Helper::loadSetElementOptionalDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    EXPECT_EQ(true, setEl->values.has_value());

    const std::set<double> correct{43.215483, 76.842907, 12.689342};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl->values.value(), tolerance);
}

TEST(SetSerializerJSONTest, OptionalWriting)
{
    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementOptionalDoubleJSON(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementOptionalDoubleJSON(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    EXPECT_EQ(true, loadedSet->values.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values.value(), loadedSet->values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST(SetSerializerJSONTest, ReadingEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEmpty.json";

    const auto setEl{Helper::loadSetElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    EXPECT_EQ(0u, setEl->values.size());
}

TEST(SetSerializerJSONTest, WritingEmpty)
{
    Helper::SetElementDouble setEl;

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDoubleJSON(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementDoubleJSON(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    EXPECT_EQ(setEl.values.size(), loadedSet->values.size());

    std::remove(fileName.c_str());
}

TEST(SetSerializerJSONTest, ReadingEnum)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.json";

    const auto setEl{Helper::loadSetElementEnumJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}

TEST(SetSerializerJSONTest, WritingEnum)
{
    Helper::SetElementEnum setEl;
    using Helper::Day;
    setEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Sunday};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementEnumJSON(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementEnumJSON(fileName)};
    ASSERT_TRUE(loadedSet.has_value());

    Helper::checkSetEquality(setEl.days, loadedSet->days, Helper::toDayString);

    std::remove(fileName.c_str());
}
