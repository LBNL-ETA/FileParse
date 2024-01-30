#include <gtest/gtest.h>

#include "FP_Set.hxx"

#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/Utility.hxx"

//#include "test/helper/files/SetElementXML.hxx"
//#include "test/helper/structures/StructureSet.hxx"

class SetSerializerTest : public testing::Test
{};

TEST_F(SetSerializerTest, DeserializationOfDoubles)
{
    auto mockData = []() {
        Helper::MockNode node{"EnumElement"};

        auto & tableNode{Helper::addChildNode(node, "Table")};

        addChildNode(tableNode, "Value", "32.497950");
        addChildNode(tableNode, "Value", "35.926622");
        addChildNode(tableNode, "Value", "42.55735499958703");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::set<double> element;
    adapter >> FileParse::Child{{"Table", "Value"}, element};

    constexpr auto tolerance{1e-6};
    const std::set<double> correct{32.49795, 35.926622, 42.557355};
    Helper::checkSetValues(correct, element, tolerance);
}

TEST_F(SetSerializerTest, SerializationOfDoubles)
{
    const std::set<double> element{932.32, 20.31, 9.392};

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << FileParse::Child{{"Table", "Value"}, element};

    auto correctNodes = []() {
        Helper::MockNode node{"BaseElement"};
        auto & tableNode{Helper::addChildNode(node, "Table")};

        addChildNode(tableNode, "Value", "9.392000");
        addChildNode(tableNode, "Value", "20.310000");
        addChildNode(tableNode, "Value", "932.320000");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}
