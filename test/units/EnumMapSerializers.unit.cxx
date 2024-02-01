#include <gtest/gtest.h>

#include <map>
#include <unordered_map>

#include "FP_Map.hxx"

#include "test/helper/Utility.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "test/helper/MockNodeAdapter.hxx"

class EnumMapSerializerTest : public testing::Test
{};

TEST_F(EnumMapSerializerTest, DeserializingEnumAsKey_String)
{
    auto mockData = []() {
        Helper::MockNode node{"MapEnumElement"};

        addChildNode(node, "Friday", "Happy");
        addChildNode(node, "Saturday", "Relax");
        addChildNode(node, "Monday", "Back to Work");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    using Helper::Day;

    std::map<Day, std::string> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Day, std::string>(
      adapter, elements, Helper::toDay);

    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, elements);
}

TEST_F(EnumMapSerializerTest, SerializingEnumAsKey_String)
{
    using Helper::Day;
    std::map<Helper::Day, std::string> days{{Day::Monday, "Value1"},
                                            {Day::Tuesday, "Value2"},
                                            {Day::Wednesday, "Value3"},
                                            {Day::Thursday, "Value4"},
                                            {Day::Friday, "Value5"}};

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Helper::Day, std::string>(
      adapter, days, Helper::toDayString);

    // Note that map will reorder elements according to key values
    auto correctNodes = []() {
        Helper::MockNode node{"MapElement"};

        addChildNode(node, "Friday", "Value5");
        addChildNode(node, "Monday", "Value1");
        addChildNode(node, "Thursday", "Value4");
        addChildNode(node, "Tuesday", "Value2");
        addChildNode(node, "Wednesday", "Value3");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(EnumMapSerializerTest, SerializingEmptyEnumMap)
{
    using Helper::Day;
    std::map<Day, std::string> emptyDays;

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Day, std::string>(
      adapter, emptyDays, Helper::toDayString);

    Helper::MockNode correctNode{"MapElement"};

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNode));
}

TEST_F(EnumMapSerializerTest, DeserializingEmptyEnumMap)
{
    Helper::MockNode emptyNode{"MapEnumElement"};
    Helper::MockNodeAdapter adapter{&emptyNode};

    std::map<Helper::Day, std::string> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Day, std::string>(
      adapter, elements, Helper::toDay);

    EXPECT_TRUE(elements.empty());
}

TEST_F(EnumMapSerializerTest, DeserializingEnumAsKey_Double)
{
    auto mockData = []() {
        Helper::MockNode node{"MapEnumElement"};

        addChildNode(node, "Red", "1.5");
        addChildNode(node, "Green", "2.5");
        addChildNode(node, "Blue", "3.5");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::map<Helper::Color, double> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Color, double>(
      adapter, elements, Helper::toColor);

    const std::map<Helper::Color, double> correct{
      {Helper::Color::Red, 1.5}, {Helper::Color::Green, 2.5}, {Helper::Color::Blue, 3.5}};

    Helper::checkMapEquality(correct, elements);
}

TEST_F(EnumMapSerializerTest, SerializingEnumAsKey_Double)
{
    std::map<Helper::Color, double> colors{
      {Helper::Color::Red, 1.1}, {Helper::Color::Green, 2.2}, {Helper::Color::Blue, 3.3}};

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Helper::Color, double>(
      adapter, colors, Helper::toColorString);

    auto correctNodes = []() {
        Helper::MockNode node{"MapElement"};

        addChildNode(node, "Blue", "3.3");
        addChildNode(node, "Green", "2.2");
        addChildNode(node, "Red", "1.1");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(EnumMapSerializerTest, DeserializingUnorderedEnumAsKey_String)
{
    auto mockData = []() {
        Helper::MockNode node{"MapEnumElement"};

        addChildNode(node, "Friday", "Happy");
        addChildNode(node, "Saturday", "Relax");
        addChildNode(node, "Monday", "Back to Work");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    using Helper::Day;

    std::unordered_map<Day, std::string> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Day, std::string>(
      adapter, elements, Helper::toDay);

    const std::unordered_map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, elements);
}

TEST_F(EnumMapSerializerTest, SerializingUnorderedEnumAsKey_String)
{
    using Helper::Day;
    std::unordered_map<Day, std::string> days{{Day::Monday, "Value1"},
                                              {Day::Tuesday, "Value2"},
                                              {Day::Wednesday, "Value3"},
                                              {Day::Thursday, "Value4"},
                                              {Day::Friday, "Value5"}};

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Day, std::string>(
      adapter, days, Helper::toDayString);

    auto correctNodes = []() {
        Helper::MockNode node{"MapElement"};

        addChildNode(node, "Friday", "Value5");
        addChildNode(node, "Monday", "Value1");
        addChildNode(node, "Thursday", "Value4");
        addChildNode(node, "Tuesday", "Value2");
        addChildNode(node, "Wednesday", "Value3");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

TEST_F(EnumMapSerializerTest, SerializingEmptyUnorderedEnumMap)
{
    using Helper::Day;
    std::unordered_map<Day, std::string> emptyDays;

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Day, std::string>(
      adapter, emptyDays, Helper::toDayString);

    Helper::MockNode correctNode{"MapElement"};

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNode));
}

TEST_F(EnumMapSerializerTest, DeserializingEmptyUnorderedEnumMap)
{
    Helper::MockNode emptyNode{"MapEnumElement"};
    Helper::MockNodeAdapter adapter{&emptyNode};

    std::unordered_map<Helper::Day, std::string> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Day, std::string>(
      adapter, elements, Helper::toDay);

    EXPECT_TRUE(elements.empty());
}