#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(MapKeyAsStructureSerializerXMLTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "CMAElement.xml";

    const auto mapEl{Helper::loadCMAElement(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};

    Helper::checkMapEquality(correct.options, mapEl->options);
}

TEST(MapKeyAsStructureSerializerXMLTest, Writing)
{
    const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
                                          {{"High", "High"}, {1.731, 7.39}}};

    const std::string expectedContent{"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                                      "<Test>\n"
                                      "\t<Element>\n"
                                      "\t\t<Glazing>High</Glazing>\n"
                                      "\t\t<Spacer>High</Spacer>\n"
                                      "\t\t<Conductivity>1.731</Conductivity>\n"
                                      "\t\t<FilmCoefficient>7.39</FilmCoefficient>\n"
                                      "\t</Element>\n"
                                      "\t<Element>\n"
                                      "\t\t<Glazing>Low</Glazing>\n"
                                      "\t\t<Spacer>Low</Spacer>\n"
                                      "\t\t<Conductivity>12.34</Conductivity>\n"
                                      "\t\t<FilmCoefficient>2.98</FilmCoefficient>\n"
                                      "\t</Element>\n"
                                      "</Test>\n"};

    const std::string fileName{"TestWrite.xml"};
    const auto result{Helper::saveCMAElement(knownElement, fileName)};
    EXPECT_EQ(result, 0) << "Error saving CMAElement!";

    const std::string serializedContent{File::loadToString(fileName)};

    EXPECT_EQ(serializedContent, expectedContent)
      << "Serialized content does not match expected content!";

    std::filesystem::remove(fileName);
}
