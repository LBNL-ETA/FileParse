#include <gtest/gtest.h>

#include "helper/Utility.hxx"

#include "helper/TestXML.hxx"
#include "helper/TestStructures.hxx"

#include "helper/FileManipulation.hxx"
#include "helper/TestSerializers.hxx"

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

    Helper::VectorElement vectorEl{Helper::loadVectorElement(fileName)};

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

    Helper::VectorElement loadedVector{Helper::loadVectorElement(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(vectorEl.values, loadedVector.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(VectorSerializerTest, TestReadingOptionalVector)
{
    const std::string fileContent{Helper::testVectorElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    Helper::OptionalVectorElement vectorEl{Helper::loadOptionalVectorElement(fileName)};

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, vectorEl.values.value(), tolerance);

    std::remove(fileName.c_str());
}