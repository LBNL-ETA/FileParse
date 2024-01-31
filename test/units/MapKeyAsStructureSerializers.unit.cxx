#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/structures/CMAStringOptions.hxx"
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


template<typename MapType>
void checkCMAValuesMap(const MapType & expected, const MapType & actual, double tolerance)
{
    static_assert(Helper::is_valid_map<MapType>::value, "MapType must be a map or unordered_map");

    ASSERT_EQ(expected.size(), actual.size());

    for(const auto & [expectedKey, expectedValue] : expected)
    {
        auto actualIter = actual.find(expectedKey);
        ASSERT_NE(actualIter, actual.end());
        const auto & actualValue = actualIter->second;

        compareCMAValues(expectedValue, actualValue, tolerance);
    }
}

TEST_F(MapKeyAsStructureSerializerTest, DeserializationUnorderedMap)
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

    std::unordered_map<Helper::CMAStringOptions, Helper::CMAValues> element;
    FileParse::deserializeMapAsChilds(adapter, "Element", element);

    const std::unordered_map<Helper::CMAStringOptions, Helper::CMAValues> correct{
      {{"Low", "Low"}, {12.34, 2.98}}, {{"High", "High"}, {1.731, 7.39}}};

    constexpr auto tolerance{1e-6};
    checkCMAValuesMap(correct, element, tolerance);
}

TEST_F(MapKeyAsStructureSerializerTest, SerializationUnorderedMap)
{
    std::unordered_map<Helper::CMAStringOptions, Helper::CMAValues> element{
      {{"Low", "Low"}, {12.34, 2.98}}, {{"High", "High"}, {1.731, 7.39}}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeMapAsChilds(adapter, "Element", element);

    // Note that map will reorder elements according to key values
    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child1{Helper::addChildNode(node, "Element")};

        addChildNode(child1, "Glazing", "High");
        addChildNode(child1, "Spacer", "High");
        addChildNode(child1, "Conductivity", "1.731000");
        addChildNode(child1, "FilmCoefficient", "7.390000");

        auto & child2{Helper::addChildNode(node, "Element")};

        addChildNode(child2, "Glazing", "Low");
        addChildNode(child2, "Spacer", "Low");
        addChildNode(child2, "Conductivity", "12.340000");
        addChildNode(child2, "FilmCoefficient", "2.980000");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(MapKeyAsStructureSerializerTest, DeserializationOrderedMap) {
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child1 = Helper::addChildNode(node, "Element");

        addChildNode(child1, "Glazing", "Medium");
        addChildNode(child1, "Spacer", "Medium");
        addChildNode(child1, "Conductivity", "3.45");
        addChildNode(child1, "FilmCoefficient", "1.23");

        auto & child2 = Helper::addChildNode(node, "Element");

        addChildNode(child2, "Glazing", "High");
        addChildNode(child2, "Spacer", "High");
        addChildNode(child2, "Conductivity", "4.56");
        addChildNode(child2, "FilmCoefficient", "2.34");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::map<Helper::CMAStringOptions, Helper::CMAValues> element;
    FileParse::deserializeMapAsChilds(adapter, "Element", element);

    const std::map<Helper::CMAStringOptions, Helper::CMAValues> correct{
      {{"Medium", "Medium"}, {3.45, 1.23}}, {{"High", "High"}, {4.56, 2.34}}};

    constexpr auto tolerance = 1e-6;
    checkCMAValuesMap(correct, element, tolerance);
}

TEST_F(MapKeyAsStructureSerializerTest, SerializationOrderedMap) {
    std::map<Helper::CMAStringOptions, Helper::CMAValues> element{
      {{"Medium", "Medium"}, {3.45, 1.23}}, {{"High", "High"}, {4.56, 2.34}}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeMapAsChilds(adapter, "Element", element);

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child1 = Helper::addChildNode(node, "Element");

        addChildNode(child1, "Glazing", "High");
        addChildNode(child1, "Spacer", "High");
        addChildNode(child1, "Conductivity", "4.560000");
        addChildNode(child1, "FilmCoefficient", "2.340000");

        auto & child2 = Helper::addChildNode(node, "Element");

        addChildNode(child2, "Glazing", "Medium");
        addChildNode(child2, "Spacer", "Medium");
        addChildNode(child2, "Conductivity", "3.450000");
        addChildNode(child2, "FilmCoefficient", "1.230000");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}
