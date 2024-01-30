#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/structures/CMAOptions.hxx"
#include "test/helper/serializers/SerializerCMAOptions.hxx"

class MapKeyAsStructureSerializerTest : public testing::Test
{};

void compareCMAValues(const Helper::CMAValues & expected,
                      const Helper::CMAValues & actual,
                      double tolerance)
{
    EXPECT_NEAR(expected.conductivity, actual.conductivity, tolerance);
    EXPECT_NEAR(expected.filmCoefficient, actual.filmCoefficient, tolerance);
}


void checkCMAValuesMap(const std::unordered_map<Helper::CMAOptions, Helper::CMAValues> & expected,
                       const std::unordered_map<Helper::CMAOptions, Helper::CMAValues> & actual,
                       double tolerance)
{
    ASSERT_EQ(expected.size(), actual.size());

    for(const auto & [expectedKey, expectedValue] : expected)
    {
        auto actualIter = actual.find(expectedKey);
        ASSERT_NE(actualIter, actual.end());
        const auto & actualValue = actualIter->second;

        compareCMAValues(expectedValue, actualValue, tolerance);
    }
}


TEST_F(MapKeyAsStructureSerializerTest, Deserialization)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child1{Helper::addChildNode(node, "Element")};

        addChildNode(child1, "Glazing", "Low");
        addChildNode(child1, "Spacer", "Low");
        addChildNode(child1, "Conductivity", "12.34");
        addChildNode(child1, "FilmCoefficient", "2.98");

        auto & child2{Helper::addChildNode(node, "Element")};

        addChildNode(child2, "Glazing", "High");
        addChildNode(child2, "Spacer", "High");
        addChildNode(child2, "Conductivity", "1.731");
        addChildNode(child2, "FilmCoefficient", "7.39");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::unordered_map<Helper::CMAOptions, Helper::CMAValues> element;
    FileParse::deserializeMapAsChilds(adapter, "Element", element);

    const std::unordered_map<Helper::CMAOptions, Helper::CMAValues> correct{
      {{"Low", "Low"}, {12.34, 2.98}}, {{"High", "High"}, {1.731, 7.39}}};

    constexpr auto tolerance{1e-6};
    checkCMAValuesMap(correct, element, tolerance);
}

// TEST_F(MapKeyAsStructureSerializerTest, Writing)
//{
//     const Helper::CMAElement knownElement{{{"Low", "Low"}, {12.34, 2.98}},
//                                           {{"High", "High"}, {1.731, 7.39}}};
//
//     const std::string expectedContent{"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                                       "<Test>\n"
//                                       "\t<Element>\n"
//                                       "\t\t<Glazing>High</Glazing>\n"
//                                       "\t\t<Spacer>High</Spacer>\n"
//                                       "\t\t<Conductivity>1.731000</Conductivity>\n"
//                                       "\t\t<FilmCoefficient>7.390000</FilmCoefficient>\n"
//                                       "\t</Element>\n"
//                                       "\t<Element>\n"
//                                       "\t\t<Glazing>Low</Glazing>\n"
//                                       "\t\t<Spacer>Low</Spacer>\n"
//                                       "\t\t<Conductivity>12.340000</Conductivity>\n"
//                                       "\t\t<FilmCoefficient>2.980000</FilmCoefficient>\n"
//                                       "\t</Element>\n"
//                                       "</Test>\n"};
//
//     const auto result{Helper::saveCMAElement(knownElement, fileName())};
//     EXPECT_EQ(result, 0) << "Error saving CMAElement!";
//
//     const std::string serializedContent{File::loadToString(fileName())};
//
//     EXPECT_EQ(serializedContent, expectedContent)
//       << "Serialized content does not match expected content!";
// }
