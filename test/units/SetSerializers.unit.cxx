#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/SetElementXML.hxx"
#include "test/helper/structures/StructureSet.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/SetSerializers.hxx"

class SetSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(SetSerializerTest, TestReadingSet)
{
    const std::string fileContent{Helper::testSetElementDoubleDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto setEl{Helper::loadSetElementDouble(fileName)};

    const std::set<double> correct{932.32, 20.31, 9.392};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl.values, tolerance);

    std::remove(fileName.c_str());
}

//TEST_F(SetSerializerTest, TestWritingSet)
//{
//    Helper::VectorElement vectorEl;
//    vectorEl.values = {1, 2, 3, 4, 5};
//
//    const std::string fileName{"TestWrite.xml"};
//
//    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
//    std::remove(fileName.c_str());
//
//    Helper::saveVectorElement(vectorEl, fileName);
//
//    const auto loadedVector{Helper::loadVectorElement(fileName)};
//
//    constexpr auto tolerance{1e-6};
//    Helper::checkVectorValues(vectorEl.values, loadedVector.values, tolerance);
//
//    std::remove(fileName.c_str());
//}