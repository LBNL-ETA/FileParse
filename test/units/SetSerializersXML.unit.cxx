#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/SetElementXML.hxx"
#include "test/helper/structures/StructureSet.hxx"

#include "test/helper/FileManipulation.hxx"

class SetSerializerXMLTest : public testing::Test
{};

TEST_F(SetSerializerXMLTest, Reading)
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

TEST_F(SetSerializerXMLTest, Writing)
{
    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDouble(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadSetElementDouble(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values, loadedVector.values, tolerance);

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerXMLTest, OptionalReading)
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

TEST_F(SetSerializerXMLTest, OptionalWriting)
{
    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementOptionalDouble(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementOptionalDouble(fileName)};

    EXPECT_EQ(true, loadedSet.values.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkSetValues(setEl.values.value(), loadedSet.values.value(), tolerance);

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerXMLTest, ReadingEmpty)
{
    const std::string fileContent{Helper::testSetElementEmptyDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto setEl{Helper::loadSetElementDouble(fileName)};

    EXPECT_EQ(0u, setEl.values.size());

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerXMLTest, WritingEmpty)
{
    Helper::SetElementDouble setEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementDouble(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementDouble(fileName)};

    EXPECT_EQ(setEl.values.size(), loadedSet.values.size());

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerXMLTest, ReadingEnum)
{
    const std::string fileContent{Helper::testSetElementEnumDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto setEl{Helper::loadSetElementEnum(fileName)};

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl.days, Helper::toDayString);

    std::remove(fileName.c_str());
}

TEST_F(SetSerializerXMLTest, WritingEnum)
{
    Helper::SetElementEnum setEl;
    using Helper::Day;
    setEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Sunday};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveSetElementEnum(setEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedSet{Helper::loadSetElementEnum(fileName)};

    Helper::checkSetEquality(setEl.days, loadedSet.days, Helper::toDayString);

    std::remove(fileName.c_str());
}