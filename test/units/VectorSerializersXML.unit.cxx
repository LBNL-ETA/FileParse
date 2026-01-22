#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/VectorElement.hxx"
#include "test/helper/structures/StructureVector.hxx"

#include "test/helper/FileManipulation.hxx"

class VectorSerializerXMLTest : public testing::Test
{};

TEST_F(VectorSerializerXMLTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.xml";

    const auto vectorEl{Helper::loadVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerXMLTest, Writing)
{
    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElementXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values, loadedVector->values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerXMLTest, ReadingOptional)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorOptional.xml";

    const auto vectorEl{Helper::loadOptionalVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl->values.value(), tolerance);
}

TEST_F(VectorSerializerXMLTest, ReadingOptionalEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Empty.xml";

    const auto vectorEl{Helper::loadOptionalVectorElementXML(fileName.string())};

    EXPECT_EQ(false, vectorEl.has_value());
}

TEST_F(VectorSerializerXMLTest, WritingOptional)
{
    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElementXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values.value(), loadedVector->values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerXMLTest, WritingOptionalEmpty)
{
    Helper::OptionalVectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElementXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    EXPECT_EQ(false, loadedVector->values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerXMLTest, ReadingEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "Empty.xml";

    const auto vectorEl{Helper::loadOptionalVectorElementXML(fileName.string())};

    EXPECT_EQ(false, vectorEl.has_value());
}

TEST_F(VectorSerializerXMLTest, WritingEmpty)
{
    Helper::VectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElementXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    EXPECT_EQ(vectorEl.values.size(), loadedVector->values.size());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerXMLTest, ReadingEnum)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.xml";

    const auto vectorEl{Helper::loadEnumVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}

TEST_F(VectorSerializerXMLTest, WritingEnum)
{
    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadEnumVectorElementXML(fileName)};
    ASSERT_TRUE(loadedVector.has_value());

    Helper::checkVectorEquality(vectorEl.days, loadedVector->days, Helper::toDayString);

    std::remove(fileName.c_str());
}