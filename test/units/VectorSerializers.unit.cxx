#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/VectorElementXML.hxx"
#include "test/helper/structures/StructureVector.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/VectorSerializers.hxx"

class VectorSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(VectorSerializerTest, TestReadingVector)
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

TEST_F(VectorSerializerTest, TestWritingVector)
{
    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
    std::remove(fileName.c_str());

    Helper::saveVectorElement(vectorEl, fileName);

    const auto loadedVector{Helper::loadVectorElement(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values, loadedVector.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestReadingOptionalVector)
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

TEST_F(VectorSerializerTest, TestReadingOptionalVectorEmpty)
{
    const std::string fileContent{Helper::testVectorElementEmptyOptionalDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, vectorEl.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestWritingOptionalVector)
{
    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveOptionalVectorElement(vectorEl, fileName);

    const auto loadedVector{Helper::loadOptionalVectorElement(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values.value(), loadedVector.values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestWritingOptionalVectorEmpty)
{
    Helper::OptionalVectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveOptionalVectorElement(vectorEl, fileName);

    const auto loadedVector{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, loadedVector.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestReadingEmptyVector)
{
    const std::string fileContent{Helper::testEmptyVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadOptionalVectorElement(fileName)};

    EXPECT_EQ(false, vectorEl.values.has_value());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestWritingEmptyVector)
{
    Helper::VectorElement vectorEl;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
    std::remove(fileName.c_str());

    Helper::saveVectorElement(vectorEl, fileName);

    const auto loadedVector{Helper::loadVectorElement(fileName)};

    EXPECT_EQ(vectorEl.values.size(), loadedVector.values.size());

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestReadingEnumVector)
{
    const std::string fileContent{Helper::testDayVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadEnumVectorElement(fileName)};

    const std::vector<Helper::Day> correct{Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl.days, Helper::toDayString);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestWritingEnumVector)
{
    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveEnumVectorElement(vectorEl, fileName);

    const auto loadedVector{Helper::loadEnumVectorElement(fileName)};

    Helper::checkVectorEquality(vectorEl.days, loadedVector.days, Helper::toDayString);

    std::remove(fileName.c_str());
}