#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/VectorElementJSON.hxx"
#include "test/helper/structures/StructureVector.hxx"

#include "test/helper/FileManipulation.hxx"

class VectorSerializerJSONTest : public testing::Test
{};

TEST_F(VectorSerializerJSONTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.json";

    const auto vectorEl{Helper::loadVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerJSONTest, Writing)
{
    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.json"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElementJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values, loadedVector->values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerJSONTest, ReadingOptional)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorOptional.json";

    const auto vectorEl{Helper::loadOptionalVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl->values.value(), tolerance);
}

TEST_F(VectorSerializerJSONTest, ReadingOptionalEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Empty.json";

    const auto vectorEl{Helper::loadOptionalVectorElementJSON(fileName.string())};

    EXPECT_EQ(false, vectorEl.has_value());
}

TEST_F(VectorSerializerJSONTest, WritingOptional)
{
    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElementJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values.value(), loadedVector->values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerJSONTest, WritingOptionalEmpty)
{
    Helper::OptionalVectorElement vectorEl;

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElementJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    EXPECT_EQ(false, loadedVector->values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerJSONTest, ReadingEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Empty.json";

    const auto vectorEl{Helper::loadOptionalVectorElementJSON(fileName.string())};

    EXPECT_EQ(false, vectorEl.has_value());
}

TEST_F(VectorSerializerJSONTest, WritingEmpty)
{
    Helper::VectorElement vectorEl;

    const std::string fileName{"TestWrite.json"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElementJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    EXPECT_EQ(vectorEl.values.size(), loadedVector->values.size());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerJSONTest, ReadingEnum)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.json";

    const auto vectorEl{Helper::loadEnumVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}

TEST_F(VectorSerializerJSONTest, WritingEnum)
{
    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadEnumVectorElementJSON(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    Helper::checkVectorEquality(vectorEl.days, loadedVector->days, Helper::toDayString);

    std::remove(fileName.c_str());
}
