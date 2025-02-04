#include <gtest/gtest.h>

#include "include/fileParse/Vector.hxx"

#include "test/helper/Utility.hxx"
#include "test/helper/MockNodeAdapter.hxx"
#include "test/helper/structures/Enums.hxx"
#include "test/helper/serializers/SerializersEnum.hxx"

class VectorSerializerTest : public testing::Test
{};

TEST_F(VectorSerializerTest, DeserializeVectorOfDoubles)
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

    std::vector<double> elements;
    adapter >> FileParse::Child{{"Table", "Value"}, elements};

    const std::vector<double> correct{38.8048, 25.5758, 96.1831, 90.3927};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, elements, tolerance);
}

TEST_F(VectorSerializerTest, SerializeVectorOfDoubles)
{
    const std::vector<double> elements{38.8048, 25.5758, 96.1831, 90.3927};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Nodes", "Element"}, elements};

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Nodes")};

        addChildNode(child, "Element", "38.8048");
        addChildNode(child, "Element", "25.5758");
        addChildNode(child, "Element", "96.1831");
        addChildNode(child, "Element", "90.3927");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(VectorSerializerTest, DeserializeVectorOfEnumerators)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Table")};

        addChildNode(child, "Color", "Red");
        addChildNode(child, "Color", "Green");
        addChildNode(child, "Color", "Blue");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    using Helper::Color;

    std::vector<Color> elements;
    adapter >> FileParse::Child{{"Table", "Color"}, elements};

    const std::vector<Color> correct{Color::Red, Color::Green, Color::Blue};

    Helper::checkVectorEquality<Color>(correct, elements);
}

TEST_F(VectorSerializerTest, SerializeVectorOfEnumerators)
{
    using Helper::Color;

    const std::vector<Color> elements{Color::Green, Color::Blue, Color::Blue, Color::Green};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Colors", "Color"}, elements};

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        auto & child{Helper::addChildNode(node, "Colors")};

        addChildNode(child, "Color", "Green");
        addChildNode(child, "Color", "Blue");
        addChildNode(child, "Color", "Blue");
        addChildNode(child, "Color", "Green");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(VectorSerializerTest, DeserializeVectorOfDoublesFromRoot)
{
    auto mockData = []() {
        Helper::MockNode node{"Root"};

        addChildNode(node, "Value", "38.8048");
        addChildNode(node, "Value", "25.5758");
        addChildNode(node, "Value", "96.1831");
        addChildNode(node, "Value", "90.3927");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<double> elements;
    adapter >> FileParse::Child{"Value", elements};

    const std::vector<double> correct{38.8048, 25.5758, 96.1831, 90.3927};

    constexpr auto tolerance{1e-6};
    Helper::checkVectorValues(correct, elements, tolerance);
}

TEST_F(VectorSerializerTest, SerializeVectorOfDoublesToRoot)
{
    const std::vector<double> elements{38.8048, 25.5758, 96.1831, 90.3927};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{"Element", elements};

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        addChildNode(node, "Element", "38.8048");
        addChildNode(node, "Element", "25.5758");
        addChildNode(node, "Element", "96.1831");
        addChildNode(node, "Element", "90.3927");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}