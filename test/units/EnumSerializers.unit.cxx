#include <gtest/gtest.h>

#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/files/EnumElementXML.hxx"
#include "test/helper/structures/StructureEnum.hxx"
#include "test/helper/serializers/SerializersEnum.hxx"

class EnumSerializerTest : public testing::Test
{};

Helper::MockNode createEnumElement()
{
    Helper::MockNode node{"EnumElement"};

    addChildNode(node, "Day", "Monday");
    addChildNode(node, "Color", "Blue");

    return node;
}

TEST_F(EnumSerializerTest, ColorAndDayDeserialization)
{
    auto elementNode(createEnumElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::EnumElement element;
    adapter >> element;

    EXPECT_EQ(Helper::Day::Monday, element.day);
    EXPECT_EQ(true, element.color.has_value());
    EXPECT_EQ(Helper::Color::Blue, element.color.value());

}

TEST_F(EnumSerializerTest, ColorAndDaySerialization)
{
    Helper::EnumElement element;
    element.day = Helper::Day::Friday;
    element.color = Helper::Color::Green;

    Helper::MockNode elementNode("EnumElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    auto correctNodes = []() {
        Helper::MockNode node{"EnumElement"};

        addChildNode(node, "Day", "Friday");
        addChildNode(node, "Color", "Green");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}

Helper::MockNode createEnumElement1()
{
    Helper::MockNode node{"EnumElement"};

    addChildNode(node, "Day", "Friday");

    return node;
}

TEST_F(EnumSerializerTest, OptionalColorMissingDeserialization)
{
    auto elementNode(createEnumElement1());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::EnumElement element;
    adapter >> element;

    EXPECT_EQ(Helper::Day::Friday, element.day);
    EXPECT_EQ(false, element.color.has_value());
}

TEST_F(EnumSerializerTest, OptionalColorMissingSerialization)
{
    Helper::EnumElement element;
    element.day = Helper::Day::Wednesday;

    Helper::MockNode elementNode("EnumElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    auto correctNodes = []() {
        Helper::MockNode node{"EnumElement"};

        addChildNode(node, "Day", "Wednesday");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}