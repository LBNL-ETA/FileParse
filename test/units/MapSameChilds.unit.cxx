#include <gtest/gtest.h>

#include <fileParse/Map.hxx>

#include "test/helper/MockNodeAdapter.hxx"
#include "test/helper/Utility.hxx"

class MapSameChildsTest : public testing::Test
{};

namespace
{
    Helper::MockNode &
      addMapChildNode(Helper::MockNode & parent, const std::string & key, const std::string & value)
    {
        Helper::MockNode & child = Helper::addChildNode(parent, "Child");
        Helper::addChildNode(child, "Key", key);
        Helper::addChildNode(child, "Value", value);

        return parent;
    }

    Helper::MockNode createTestMap()
    {
        Helper::MockNode node{"MapExample"};

        addMapChildNode(node, "Key1", "Value1");
        addMapChildNode(node, "Key2", "Value2");
        addMapChildNode(node, "Key3", "Value3");

        return node;
    }
}   // namespace

TEST_F(MapSameChildsTest, DeserializeMapStringDouble)
{
    auto elementNode(createTestMap());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::map<std::string, std::string> testMap;
    FileParse::deserializeMapAsChilds(adapter, {"Child", "Key", "Value"}, testMap);

    const std::map<std::string, std::string> correct{
      {"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};

    Helper::checkMapValuesEqual(correct, testMap);
}

TEST_F(MapSameChildsTest, SerializeMapStringDouble)
{
    std::map<std::string, std::string> testMap{{"Key1", "Value1"},
                                               {"Key2", "Value2"},
                                               {"Key3", "Value3"}};

    Helper::MockNode elementNode("Root");
    Helper::MockNodeAdapter adapter{&elementNode};
    FileParse::serializeMapAsChilds(adapter, {"Child", "Key", "Value"}, testMap);

    auto correctNodes = []() {
        Helper::MockNode node{"Root"};

        addMapChildNode(node, "Key1", "Value1");
        addMapChildNode(node, "Key2", "Value2");
        addMapChildNode(node, "Key3", "Value3");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}