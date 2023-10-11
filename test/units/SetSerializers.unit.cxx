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

TEST_F(SetSerializerTest, Reading)
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

TEST_F(SetSerializerTest, Writing)
{
    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveSetElementDouble(setEl, fileName);

    const auto loadedVector{Helper::loadSetElementDouble(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values, loadedVector.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerTest, OptionalReading)
{
    const std::string fileContent{Helper::testSetElementOptionalDoubleDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto setEl{Helper::loadSetElementOptionalDouble(fileName)};

    EXPECT_EQ(true, setEl.values.has_value());

    const std::set<double> correct{43.215483, 76.842907, 12.689342};
    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(correct, setEl.values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerTest, OptionalWriting)
{
    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveSetElementOptionalDouble(setEl, fileName);

    const auto loadedVector{Helper::loadSetElementOptionalDouble(fileName)};

    EXPECT_EQ(true, loadedVector.values.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values.value(), loadedVector.values.value(), tolerance);

    std::remove(fileName.c_str());
}