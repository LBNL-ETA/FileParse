#include <gtest/gtest.h>

#include "FP_Vector.hxx"

#include "test/helper/Utility.hxx"

#include "test/helper/MockNodeAdapter.hxx"

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

        addChildNode(child, "Element", "38.804800");
        addChildNode(child, "Element", "25.575800");
        addChildNode(child, "Element", "96.183100");
        addChildNode(child, "Element", "90.392700");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}