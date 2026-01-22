/// VectorElement file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/VectorElement.hxx"
#include "test/helper/structures/StructureVector.hxx"

class VectorSerializerFileTest : public testing::Test
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

TEST_F(VectorSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.xml";

    const auto vectorEl{Helper::loadVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteVector.xml"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const auto result{Helper::saveVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values, loaded->values, tolerance);
}

TEST_F(VectorSerializerFileTest, ReadOptionalXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorOptional.xml";

    const auto vectorEl{Helper::loadOptionalVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    Helper::checkVectorValues(correct, vectorEl->values.value(), tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadOptionalXML)
{
    const std::string fileName{"TestWriteOptionalVector.xml"};
    addTempFile(fileName);

    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const auto result{Helper::saveOptionalVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadOptionalVectorElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values.value(), loaded->values.value(), tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadOptionalEmptyXML)
{
    const std::string fileName{"TestWriteOptionalEmptyVector.xml"};
    addTempFile(fileName);

    Helper::OptionalVectorElement vectorEl;

    const auto result{Helper::saveOptionalVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadOptionalVectorElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_FALSE(loaded->values.has_value());
}

TEST_F(VectorSerializerFileTest, WriteAndReadEmptyXML)
{
    const std::string fileName{"TestWriteEmptyVector.xml"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;

    const auto result{Helper::saveVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(vectorEl.values.size(), loaded->values.size());
}

TEST_F(VectorSerializerFileTest, ReadEnumXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.xml";

    const auto vectorEl{Helper::loadEnumVectorElementXML(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}

TEST_F(VectorSerializerFileTest, WriteAndReadEnumXML)
{
    const std::string fileName{"TestWriteEnumVector.xml"};
    addTempFile(fileName);

    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const auto result{Helper::saveEnumVectorElementXML(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumVectorElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorEquality(vectorEl.days, loaded->days, Helper::toDayString);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(VectorSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.json";

    const auto vectorEl{Helper::loadVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteVector.json"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;
    vectorEl.values = {1, 2, 3, 4, 5};

    const auto result{Helper::saveVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values, loaded->values, tolerance);
}

TEST_F(VectorSerializerFileTest, ReadOptionalJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorOptional.json";

    const auto vectorEl{Helper::loadOptionalVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{33.41, 28.13, 6.0756};
    Helper::checkVectorValues(correct, vectorEl->values.value(), tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadOptionalJSON)
{
    const std::string fileName{"TestWriteOptionalVector.json"};
    addTempFile(fileName);

    Helper::OptionalVectorElement vectorEl;
    vectorEl.values = {0.342561, 2.673412, 6.895461, 7.012345, 8.567890};

    const auto result{Helper::saveOptionalVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadOptionalVectorElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values.value(), loaded->values.value(), tolerance);
}

TEST_F(VectorSerializerFileTest, WriteAndReadOptionalEmptyJSON)
{
    const std::string fileName{"TestWriteOptionalEmptyVector.json"};
    addTempFile(fileName);

    Helper::OptionalVectorElement vectorEl;

    const auto result{Helper::saveOptionalVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadOptionalVectorElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_FALSE(loaded->values.has_value());
}

TEST_F(VectorSerializerFileTest, WriteAndReadEmptyJSON)
{
    const std::string fileName{"TestWriteEmptyVector.json"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;

    const auto result{Helper::saveVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(vectorEl.values.size(), loaded->values.size());
}

TEST_F(VectorSerializerFileTest, ReadEnumJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.json";

    const auto vectorEl{Helper::loadEnumVectorElementJSON(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}

TEST_F(VectorSerializerFileTest, WriteAndReadEnumJSON)
{
    const std::string fileName{"TestWriteEnumVector.json"};
    addTempFile(fileName);

    Helper::EnumVectorElement vectorEl;
    using Helper::Day;
    vectorEl.days = {Day::Monday, Day::Tuesday, Day::Thursday, Day::Friday};

    const auto result{Helper::saveEnumVectorElementJSON(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadEnumVectorElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorEquality(vectorEl.days, loaded->days, Helper::toDayString);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(VectorSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.xml";

    const auto vectorEl{Helper::loadVectorElement(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorElement.json";

    const auto vectorEl{Helper::loadVectorElement(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<double> correct{23.41, 18.13, 5.0756};
    Helper::checkVectorValues(correct, vectorEl->values, tolerance);
}

TEST_F(VectorSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteVectorUnified.xml"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;
    vectorEl.values = {1.5, 2.5, 3.5};

    const auto result{Helper::saveVectorElement(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElement(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values, loaded->values, tolerance);
}

TEST_F(VectorSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteVectorUnified.json"};
    addTempFile(fileName);

    Helper::VectorElement vectorEl;
    vectorEl.values = {1.5, 2.5, 3.5};

    const auto result{Helper::saveVectorElement(vectorEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVectorElement(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkVectorValues(vectorEl.values, loaded->values, tolerance);
}

TEST_F(VectorSerializerFileTest, UnifiedEnumReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.xml";

    const auto vectorEl{Helper::loadEnumVectorElement(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}

TEST_F(VectorSerializerFileTest, UnifiedEnumReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VectorEnum.json";

    const auto vectorEl{Helper::loadEnumVectorElement(fileName.string())};
    ASSERT_TRUE(vectorEl.has_value());

    const std::vector<Helper::Day> correct{
      Helper::Day::Friday, Helper::Day::Saturday, Helper::Day::Sunday};
    Helper::checkVectorEquality(correct, vectorEl->days, Helper::toDayString);
}
