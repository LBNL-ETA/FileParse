#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/VariantElementXML.hxx"
#include "test/helper/structures/StructureVariant.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/SerializersVariant.hxx"

class VariantSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(VariantSerializerTest, Reading)
{
    const std::string fileContent{Helper::testVariantParent()};
    const std::string fileName{"TestRead.xml"};

    std::remove(fileName.c_str());
    File::createFileFromString(fileName, fileContent);

    const auto vectorEl{Helper::loadVariantAll(fileName)};

    //const std::vector<double> correct{23.41, 18.13, 5.0756};
    //constexpr auto tolerance{1e-6};
    //Helper::checkVectorValues(correct, vectorEl.values, tolerance);

    std::remove(fileName.c_str());
}