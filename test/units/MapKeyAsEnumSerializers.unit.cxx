#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/UtilityCMA.hxx"
#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/structures/CMAEnumOptions.hxx"
#include "test/helper/serializers/SerializerCMAEnumOptions.hxx"

class MapKeyAsEnumSerializerTest : public testing::Test
{};

TEST_F(MapKeyAsEnumSerializerTest, DeserializationUnorderedMap)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child_low{Helper::addChildNode(node, "Element")};

        addChildNode(child_low, "Glazing", "Low");
        addChildNode(child_low, "Spacer", "Low");
        addChildNode(child_low, "Conductivity", "12.34");
        addChildNode(child_low, "FilmCoefficient", "2.98");

        auto & child_high{Helper::addChildNode(node, "Element")};

        addChildNode(child_high, "Glazing", "High");
        addChildNode(child_high, "Spacer", "High");
        addChildNode(child_high, "Conductivity", "1.731");
        addChildNode(child_high, "FilmCoefficient", "7.39");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::unordered_map<Helper::CMAEnumOptions, Helper::CMAValues> element;
    FileParse::deserializeMapAsChilds(adapter, "Element", element);

    const std::unordered_map<Helper::CMAEnumOptions, Helper::CMAValues> correct{
      {{Helper::Option::Low, Helper::Option::Low}, {12.34, 2.98}},
      {{Helper::Option::High, Helper::Option::High}, {1.731, 7.39}}};

    constexpr auto tolerance{1e-6};
    checkCMAValuesMap(correct, element, tolerance);
}

TEST_F(MapKeyAsEnumSerializerTest, SerializationUnorderedMap)
{
    std::unordered_map<Helper::CMAEnumOptions, Helper::CMAValues> element{
      {{Helper::Option::Low, Helper::Option::Low}, {12.34, 2.98}},
      {{Helper::Option::High, Helper::Option::High}, {1.731, 7.39}}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeMapAsChilds(adapter, "Element", element);

    // Note that map will reorder elements according to key values
    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child_high{Helper::addChildNode(node, "Element")};

        addChildNode(child_high, "Glazing", "High");
        addChildNode(child_high, "Spacer", "High");
        addChildNode(child_high, "Conductivity", "1.731000");
        addChildNode(child_high, "FilmCoefficient", "7.390000");

        auto & child_low{Helper::addChildNode(node, "Element")};

        addChildNode(child_low, "Glazing", "Low");
        addChildNode(child_low, "Spacer", "Low");
        addChildNode(child_low, "Conductivity", "12.340000");
        addChildNode(child_low, "FilmCoefficient", "2.980000");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(MapKeyAsEnumSerializerTest, DeserializationOrderedMap)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child_low = Helper::addChildNode(node, "Element");

        addChildNode(child_low, "Glazing", "Low");
        addChildNode(child_low, "Spacer", "Low");
        addChildNode(child_low, "Conductivity", "3.45");
        addChildNode(child_low, "FilmCoefficient", "1.23");

        auto & child_high = Helper::addChildNode(node, "Element");

        addChildNode(child_high, "Glazing", "High");
        addChildNode(child_high, "Spacer", "High");
        addChildNode(child_high, "Conductivity", "4.56");
        addChildNode(child_high, "FilmCoefficient", "2.34");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::map<Helper::CMAEnumOptions, Helper::CMAValues> element;
    FileParse::deserializeMapAsChilds(adapter, "Element", element);

    const std::map<Helper::CMAEnumOptions, Helper::CMAValues> correct{
      {{Helper::Option::Low, Helper::Option::Low}, {3.45, 1.23}},
      {{Helper::Option::High, Helper::Option::High}, {4.56, 2.34}}};

    constexpr auto tolerance = 1e-6;
    checkCMAValuesMap(correct, element, tolerance);
}

TEST_F(MapKeyAsEnumSerializerTest, SerializationOrderedMap)
{
    std::map<Helper::CMAEnumOptions, Helper::CMAValues> element{
      {{Helper::Option::Low, Helper::Option::Low}, {3.45, 1.23}},
      {{Helper::Option::High, Helper::Option::High}, {4.56, 2.34}}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeMapAsChilds(adapter, "Element", element);

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child_low = Helper::addChildNode(node, "Element");

        addChildNode(child_low, "Glazing", "Low");
        addChildNode(child_low, "Spacer", "Low");
        addChildNode(child_low, "Conductivity", "3.450000");
        addChildNode(child_low, "FilmCoefficient", "1.230000");

        auto & child_high = Helper::addChildNode(node, "Element");

        addChildNode(child_high, "Glazing", "High");
        addChildNode(child_high, "Spacer", "High");
        addChildNode(child_high, "Conductivity", "4.560000");
        addChildNode(child_high, "FilmCoefficient", "2.340000");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}
