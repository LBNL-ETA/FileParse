#include <gtest/gtest.h>

#include "FP_Array.hxx"

#include "test/helper/Utility.hxx"
#include "test/helper/MockNodeAdapter.hxx"
#include "test/helper/structures/Enums.hxx"
#include "test/helper/serializers/SerializersEnum.hxx"

class ArraySerializerTest : public testing::Test
{};

TEST_F(ArraySerializerTest, DeserializeArrayOfDoubles)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Value", "38.8048");
        addChildNode(child, "Value", "25.5758");
        addChildNode(child, "Value", "96.1831");
        addChildNode(child, "Value", "90.3927");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::array<double, 4> elements{0, 0, 0, 0};
    adapter >> FileParse::Child{{"Table", "Value"}, elements};

    const std::array<double, 4> correct{38.8048, 25.5758, 96.1831, 90.3927};

    constexpr auto tolerance{1e-6};
    Helper::checkArrayValues(correct, elements, tolerance);
}

TEST_F(ArraySerializerTest, DeserializeArrayOfDoublesIncomplete)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Value", "38.8048");
        addChildNode(child, "Value", "25.5758");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::array<double, 4> elements{0, 0, 0, 0};
    adapter >> FileParse::Child{{"Table", "Value"}, elements};

    const std::array<double, 4> correct{38.8048, 25.5758, 0, 0};

    constexpr auto tolerance{1e-6};
    Helper::checkArrayValues(correct, elements, tolerance);
}

TEST_F(ArraySerializerTest, DeserializeArrayOfDoublesExtraData)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Value", "38.8048");
        addChildNode(child, "Value", "25.5758");
        addChildNode(child, "Value", "96.1831");
        addChildNode(child, "Value", "90.3927");
        addChildNode(child, "Value", "192.1831");
        addChildNode(child, "Value", "190.3927");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::array<double, 4> elements{0, 0, 0, 0};
    adapter >> FileParse::Child{{"Table", "Value"}, elements};

    const std::array<double, 4> correct{38.8048, 25.5758, 96.1831, 90.3927};

    constexpr auto tolerance{1e-6};
    Helper::checkArrayValues(correct, elements, tolerance);
}

TEST_F(ArraySerializerTest, SerializeArrayOfDoubles)
{
    std::array<double, 4> elements{38.8048, 25.5758, 96.1831, 90.3927};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << FileParse::Child{{"Table", "Value"}, elements};

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};
        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Value", "38.8048");
        addChildNode(child, "Value", "25.5758");
        addChildNode(child, "Value", "96.1831");
        addChildNode(child, "Value", "90.3927");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(ArraySerializerTest, DeserializeArrayOfEnumerators)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Color", "Blue");
        addChildNode(child, "Color", "Green");
        addChildNode(child, "Color", "Red");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::array<Helper::Color, 3> elements{
      Helper::Color::Blue, Helper::Color::Blue, Helper::Color::Blue};
    adapter >> FileParse::Child{{"Table", "Color"}, elements};

    const std::array<Helper::Color, 3> correct{
      Helper::Color::Blue, Helper::Color::Green, Helper::Color::Red};

    Helper::checkArrayEquality(correct, elements);
}

TEST_F(ArraySerializerTest, SerializeArrayOfEnumerators)
{
    std::array<Helper::Color, 3> elements{
      Helper::Color::Blue, Helper::Color::Green, Helper::Color::Red};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << FileParse::Child{{"Table", "Color"}, elements};

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};
        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Color", "Blue");
        addChildNode(child, "Color", "Green");
        addChildNode(child, "Color", "Red");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}