#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/VectorElementXML.hxx"
#include "test/helper/structures/StructureVector.hxx"

#include "test/helper/FileManipulation.hxx"

class VectorSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(VectorSerializerTest, Reading)
{
    const std::string fileContent{Helper::testVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadVectorElement(fileName)};

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, Writing)
{
    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElement(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElement(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values, loadedVector.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, ReadingOptional)
{
    const std::string fileContent{Helper::testVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadOptionalVectorElement(fileName)};

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl.values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, ReadingOptionalEmpty)
{
    const std::string fileContent{Helper::testVectorElementEmptyOptionalDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, vectorEl.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, WritingOptional)
{
    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElement(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElement(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values.value(), loadedVector.values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, WritingOptionalEmpty)
{
    Helper::OptionalVectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveOptionalVectorElement(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, loadedVector.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, ReadingEmpty)
{
    const std::string fileContent{Helper::testEmptyVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, vectorEl.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, WritingEmpty)
{
    Helper::VectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveVectorElement(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadVectorElement(fileName)};

    EXPECT_EQ(vectorEl.values.size(), loadedVector.values.size());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, ReadingEnum)
{
    const std::string fileContent{Helper::testDayVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadEnumVectorElement(fileName)};

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl.days, Helper::toDayString);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, WritingEnum)
{
    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveEnumVectorElement(vectorEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadEnumVectorElement(fileName)};

    Helper::checkVectorEquality(vectorEl.days, loadedVector.days, Helper::toDayString);

    std::remove(fileName.c_str());
}