#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/CMAOptions.hxx"

#include "test/helper/FileManipulation.hxx"

class MapKeyAsStructureSerializerXMLTest : public testing::Test
{
private:
    const std::string m_FileName{"Test.xml"};

protected:
    void SetUp() override
    {
        std::remove(m_FileName.c_str());
    }

    void TearDown() override
    {
        std::remove(m_FileName.c_str());
    }

public:
    [[nodiscard]] std::string fileName() const
    {
        return m_FileName;
    }
};

TEST_F(MapKeyAsStructureSerializerXMLTest, Reading)
{
    const std::string fileContent{Helper::testCMAElementDatabase()};

    File::createFileFromString(fileName(), fileContent);

    const auto mapEl{Helper::loadCMAElement(fileName())};

    const Helper::CMAElement correct{{{"Low", "Low"}, {12.34, 2.98}},
                                     {{"High", "High"}, {1.731, 7.39}}};

    Helper::checkMapEquality(correct.options, mapEl.options);
}

TEST_F(MapKeyAsStructureSerializerXMLTest, Writing)
{
    const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
                                          {{"High", "High"}, {1.731, 7.39}}};

    const std::string expectedContent{"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                                      "<Test>\n"
                                      "\t<Element>\n"
                                      "\t\t<Glazing>High</Glazing>\n"
                                      "\t\t<Spacer>High</Spacer>\n"
                                      "\t\t<Conductivity>1.731000</Conductivity>\n"
                                      "\t\t<FilmCoefficient>7.390000</FilmCoefficient>\n"
                                      "\t</Element>\n"
                                      "\t<Element>\n"
                                      "\t\t<Glazing>Low</Glazing>\n"
                                      "\t\t<Spacer>Low</Spacer>\n"
                                      "\t\t<Conductivity>12.340000</Conductivity>\n"
                                      "\t\t<FilmCoefficient>2.980000</FilmCoefficient>\n"
                                      "\t</Element>\n"
                                      "</Test>\n"};

    const auto result{Helper::saveCMAElement(knownElement, fileName())};
    EXPECT_EQ(result, 0) << "Error saving CMAElement!";

    const std::string serializedContent{File::loadToString(fileName())};

    EXPECT_EQ(serializedContent, expectedContent)
      << "Serialized content does not match expected content!";
}
