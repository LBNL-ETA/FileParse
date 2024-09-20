#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"
#include "test/helper/serializers/SerializersMap.hxx"

#include "test/helper/MockNodeAdapter.hxx"

class DoubleMapSerializerTest : public testing::Test
{};

Helper::MockNode createStringDoubleMapElement()
{
    Helper::MockNode node{"child"};
    Helper::MockNode & mapNode = Helper::addChildNode(node, "MapDouble");

    addChildNode(mapNode, "Key1", "37.582914");
    addChildNode(mapNode, "Key2", "92.143057");
    addChildNode(mapNode, "Key3", "15.907634");

    return node;
}

TEST_F(DoubleMapSerializerTest, DeserializeMapStringDouble)
{
    auto elementNode(createStringDoubleMapElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::MapElementDouble element;
    adapter >> element;

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};

    constexpr auto tolerance{1e-6};
    Helper::checkMapValues(correct, element.values, tolerance);
}

TEST_F(DoubleMapSerializerTest, SerializeMapStringDouble)
{
    Helper::MapElementDouble mapEl;
    mapEl.values = {{"Value1", 23.856912},
                    {"Value2", 67.431280},
                    {"Value3", 14.903215},
                    {"Value4", 98.540127},
                    {"Value5", 51.284960}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << mapEl;

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};
        Helper::MockNode & mapNode = Helper::addChildNode(node, "MapDouble");

        addChildNode(mapNode, "Value1", "23.856912");
        addChildNode(mapNode, "Value2", "67.43128");
        addChildNode(mapNode, "Value3", "14.903215");
        addChildNode(mapNode, "Value4", "98.540127");
        addChildNode(mapNode, "Value5", "51.28496");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}