#include <gtest/gtest.h>

#include "test/helper/MockNodeAdapter.hxx"

#include "test/helper/files/EnumElement.hxx"
#include "test/helper/structures/StructureEnum.hxx"
#include "test/helper/serializers/SerializersEnum.hxx"

class EnumSerializerTest : public testing::Test
{};

TEST_F(EnumSerializerTest, ColorAndDayDeserialization)
{
    auto mockData = []() {
        Helper::MockNode node{"EnumElement"};

        addChildNode(node, "Day", "Monday");
        addChildNode(node, "Color", "Blue");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::EnumElement element;
    adapter >> element;

    EXPECT_EQ(static_cast<int>(Helper::Day::Monday), static_cast<int>(element.day));
    EXPECT_EQ(true, element.color.has_value());
    EXPECT_EQ(static_cast<int>(Helper::Color::Blue), static_cast<int>(element.color.value()));
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

TEST_F(EnumSerializerTest, OptionalColorMissingDeserialization)
{
    auto mockData = []() {
        Helper::MockNode node{"EnumElement"};

        addChildNode(node, "Day", "Friday");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::EnumElement element;
    adapter >> element;

    EXPECT_EQ(static_cast<int>(Helper::Day::Friday), static_cast<int>(element.day));
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