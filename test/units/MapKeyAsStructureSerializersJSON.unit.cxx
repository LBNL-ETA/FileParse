#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementJSON.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(MapKeyAsStructureSerializerJSONTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.json";

    const auto mapEl{Helper::loadCMAElementJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};

    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST(MapKeyAsStructureSerializerJSONTest, Writing)
{
    const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
                                          {{"High", "High"}, {1.731, 7.39}}};

    const std::string fileName{"TestWrite.json"};
    const auto result{Helper::saveCMAElementJSON(knownElement, fileName)};
    EXPECT_EQ(result, 0) << "Error saving CMAElement!";

    // Load back and verify
    const auto loadedElement{Helper::loadCMAElementJSON(fileName)};
    ASSERT_TRUE(loadedElement.has_value());

    Helper::checkMapEquality(knownElement.options, loadedElement->options);

    std::filesystem::remove(fileName);
}
