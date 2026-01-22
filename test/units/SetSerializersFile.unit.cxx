/// SetElement file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/SetElement.hxx"
#include "test/helper/structures/StructureSet.hxx"

class SetSerializerFileTest : public testing::Test
{
protected:
    void TearDown() override
    {
        for(const auto & file : tempFiles)
        {
            std::remove(file.c_str());
        }
    }

    void addTempFile(const std::string & name)
    {
        tempFiles.push_back(name);
    }

    std::vector<std::string> tempFiles;
    static constexpr auto tolerance{1e-6};
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(SetSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.xml";

    const auto setEl{Helper::loadSetElementDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST_F(SetSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteSet.xml"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const auto result{Helper::saveSetElementDoubleXML(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDoubleXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetValues(setEl.values, loaded->values, tolerance);
}

TEST_F(SetSerializerFileTest, ReadOptionalXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableOptional.xml";

    const auto setEl{Helper::loadSetElementOptionalDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());
    EXPECT_TRUE(setEl->values.has_value());

    const std::set<double> correct{43.215483, 76.842907, 12.689342};
    Helper::checkSetValues(correct, setEl->values.value(), tolerance);
}

TEST_F(SetSerializerFileTest, WriteAndReadOptionalXML)
{
    const std::string fileName{"TestWriteOptionalSet.xml"};
    addTempFile(fileName);

    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const auto result{Helper::saveSetElementOptionalDoubleXML(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementOptionalDoubleXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_TRUE(loaded->values.has_value());
    Helper::checkSetValues(setEl.values.value(), loaded->values.value(), tolerance);
}

TEST_F(SetSerializerFileTest, ReadEmptyXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEmpty.xml";

    const auto setEl{Helper::loadSetElementDoubleXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());
    EXPECT_EQ(0u, setEl->values.size());
}

TEST_F(SetSerializerFileTest, WriteAndReadEmptyXML)
{
    const std::string fileName{"TestWriteEmptySet.xml"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;

    const auto result{Helper::saveSetElementDoubleXML(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDoubleXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(setEl.values.size(), loaded->values.size());
}

TEST_F(SetSerializerFileTest, ReadEnumXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.xml";

    const auto setEl{Helper::loadSetElementEnumXML(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}

TEST_F(SetSerializerFileTest, WriteAndReadEnumXML)
{
    const std::string fileName{"TestWriteEnumSet.xml"};
    addTempFile(fileName);

    Helper::SetElementEnum setEl;
    using Helper::Day;
    setEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Sunday};

    const auto result{Helper::saveSetElementEnumXML(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementEnumXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetEquality(setEl.days, loaded->days, Helper::toDayString);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(SetSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.json";

    const auto setEl{Helper::loadSetElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST_F(SetSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteSet.json"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;
    setEl.values = {1, 2, 3, 4, 5};

    const auto result{Helper::saveSetElementDoubleJSON(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDoubleJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetValues(setEl.values, loaded->values, tolerance);
}

TEST_F(SetSerializerFileTest, ReadOptionalJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableOptional.json";

    const auto setEl{Helper::loadSetElementOptionalDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());
    EXPECT_TRUE(setEl->values.has_value());

    const std::set<double> correct{43.215483, 76.842907, 12.689342};
    Helper::checkSetValues(correct, setEl->values.value(), tolerance);
}

TEST_F(SetSerializerFileTest, WriteAndReadOptionalJSON)
{
    const std::string fileName{"TestWriteOptionalSet.json"};
    addTempFile(fileName);

    Helper::SetElementOptionalDouble setEl;
    setEl.values = {11, 12, 13, 14, 15};

    const auto result{Helper::saveSetElementOptionalDoubleJSON(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementOptionalDoubleJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_TRUE(loaded->values.has_value());
    Helper::checkSetValues(setEl.values.value(), loaded->values.value(), tolerance);
}

TEST_F(SetSerializerFileTest, ReadEmptyJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEmpty.json";

    const auto setEl{Helper::loadSetElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());
    EXPECT_EQ(0u, setEl->values.size());
}

TEST_F(SetSerializerFileTest, WriteAndReadEmptyJSON)
{
    const std::string fileName{"TestWriteEmptySet.json"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;

    const auto result{Helper::saveSetElementDoubleJSON(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDoubleJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(setEl.values.size(), loaded->values.size());
}

TEST_F(SetSerializerFileTest, ReadEnumJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.json";

    const auto setEl{Helper::loadSetElementEnumJSON(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}

TEST_F(SetSerializerFileTest, WriteAndReadEnumJSON)
{
    const std::string fileName{"TestWriteEnumSet.json"};
    addTempFile(fileName);

    Helper::SetElementEnum setEl;
    using Helper::Day;
    setEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Sunday};

    const auto result{Helper::saveSetElementEnumJSON(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementEnumJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetEquality(setEl.days, loaded->days, Helper::toDayString);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(SetSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.xml";

    const auto setEl{Helper::loadSetElementDouble(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST_F(SetSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableDouble.json";

    const auto setEl{Helper::loadSetElementDouble(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<double> correct{932.32, 20.31, 9.392};
    Helper::checkSetValues(correct, setEl->values, tolerance);
}

TEST_F(SetSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteSetUnified.xml"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;
    setEl.values = {1.5, 2.5, 3.5};

    const auto result{Helper::saveSetElementDouble(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDouble(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetValues(setEl.values, loaded->values, tolerance);
}

TEST_F(SetSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteSetUnified.json"};
    addTempFile(fileName);

    Helper::SetElementDouble setEl;
    setEl.values = {1.5, 2.5, 3.5};

    const auto result{Helper::saveSetElementDouble(setEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadSetElementDouble(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkSetValues(setEl.values, loaded->values, tolerance);
}

TEST_F(SetSerializerFileTest, UnifiedEnumReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.xml";

    const auto setEl{Helper::loadSetElementEnum(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}

TEST_F(SetSerializerFileTest, UnifiedEnumReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "SetWithTableEnum.json";

    const auto setEl{Helper::loadSetElementEnum(fileName.string())};
    ASSERT_TRUE(setEl.has_value());

    const std::set<Helper::Day> correct{
      Helper::Day::Wednesday, Helper::Day::Friday, Helper::Day::Sunday};
    Helper::checkSetEquality(correct, setEl->days, Helper::toDayString);
}
