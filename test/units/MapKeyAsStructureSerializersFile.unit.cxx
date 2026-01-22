/// MapKeyAsStructure file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "test/helper/FileManipulation.hxx"

class MapKeyAsStructureSerializerFileTest : public testing::Test
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
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(MapKeyAsStructureSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.xml";

    const auto mapEl{Helper::loadCMAElementXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};
    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST_F(MapKeyAsStructureSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteCMA.xml"};
    addTempFile(fileName);

    const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
                                          {{"High", "High"}, {1.731, 7.39}}};

    const auto result{Helper::saveCMAElementXML(knownElement, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadCMAElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(knownElement.options, loaded->options);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(MapKeyAsStructureSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.json";

    const auto mapEl{Helper::loadCMAElementJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};
    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST_F(MapKeyAsStructureSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteCMA.json"};
    addTempFile(fileName);

    const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
                                          {{"High", "High"}, {1.731, 7.39}}};

    const auto result{Helper::saveCMAElementJSON(knownElement, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadCMAElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(knownElement.options, loaded->options);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(MapKeyAsStructureSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.xml";

    const auto mapEl{Helper::loadCMAElement(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};
    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST_F(MapKeyAsStructureSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.json";

    const auto mapEl{Helper::loadCMAElement(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};
    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST_F(MapKeyAsStructureSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteCMAUnified.xml"};
    addTempFile(fileName);

    const Helper::CMAElement element{{{"Test", "Test"}, {5.5, 6.6}}};

    const auto result{Helper::saveCMAElement(element, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadCMAElement(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(element.options, loaded->options);
}

TEST_F(MapKeyAsStructureSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteCMAUnified.json"};
    addTempFile(fileName);

    const Helper::CMAElement element{{{"Test", "Test"}, {5.5, 6.6}}};

    const auto result{Helper::saveCMAElement(element, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadCMAElement(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(element.options, loaded->options);
}
