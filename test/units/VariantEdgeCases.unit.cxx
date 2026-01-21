/// Variant edge case tests to improve branch coverage
#include <gtest/gtest.h>

#include <fileParse/Variant.hxx>
#include <fileParse/Vector.hxx>

#include "test/helper/MockNodeAdapter.hxx"

//////////////////////////////////////////////////////////////////////////////
// Variant.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(VariantEdgeCases, SerializeVariantIndexOutOfBounds)
{
    // Variant with index that exceeds nodeNames size
    std::variant<int, std::string, double> v = 3.14;   // index 2

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Only provide 2 node names but variant is at index 2
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    // Should not crash, should just not serialize (index >= nodeNames.size())
    FileParse::serializeVariant(adapter, nodeNames, v);

    // No child should be added since index 2 >= nodeNames.size() (2)
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VariantEdgeCases, SerializeVariantValidIndex)
{
    std::variant<int, std::string> v = 42;   // index 0

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};
    FileParse::serializeVariant(adapter, nodeNames, v);

    // Should have child "IntValue"
    ASSERT_EQ(1u, adapter.getNode().child.size());
    EXPECT_EQ("IntValue", adapter.getNode().child[0].tag);
    EXPECT_EQ("42", adapter.getNode().child[0].text);
}

TEST(VariantEdgeCases, DeserializeVariantNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No matching children
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::variant<int, std::string> v = 0;   // default value
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    FileParse::deserializeVariant(adapter, nodeNames, v);

    // Should remain at default (int with value 0)
    EXPECT_TRUE(std::holds_alternative<int>(v));
    EXPECT_EQ(0, std::get<int>(v));
}

TEST(VariantEdgeCases, DeserializeVariantFirstTypeMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        Helper::addChildNode(node, "IntValue", "123");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::variant<int, std::string> v;
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    FileParse::deserializeVariant(adapter, nodeNames, v);

    EXPECT_TRUE(std::holds_alternative<int>(v));
    EXPECT_EQ(123, std::get<int>(v));
}

TEST(VariantEdgeCases, DeserializeVariantSecondTypeMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        Helper::addChildNode(node, "StringValue", "hello");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::variant<int, std::string> v;
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    FileParse::deserializeVariant(adapter, nodeNames, v);

    EXPECT_TRUE(std::holds_alternative<std::string>(v));
    EXPECT_EQ("hello", std::get<std::string>(v));
}

TEST(VariantEdgeCases, SerializeOptionalVariantEmpty)
{
    std::optional<std::variant<int, std::string>> optVar = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};
    FileParse::serializeOptionalVariant(adapter, nodeNames, optVar);

    // No children should be added
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VariantEdgeCases, SerializeOptionalVariantWithValue)
{
    std::optional<std::variant<int, std::string>> optVar = std::string("test");

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};
    FileParse::serializeOptionalVariant(adapter, nodeNames, optVar);

    ASSERT_EQ(1u, adapter.getNode().child.size());
    EXPECT_EQ("StringValue", adapter.getNode().child[0].tag);
}

TEST(VariantEdgeCases, DeserializeOptionalVariantNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::variant<int, std::string>> optVar;
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    FileParse::deserializeOptionalVariant(adapter, nodeNames, optVar);

    // Should be nullopt
    EXPECT_FALSE(optVar.has_value());
}

TEST(VariantEdgeCases, DeserializeOptionalVariantMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        Helper::addChildNode(node, "IntValue", "99");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::variant<int, std::string>> optVar;
    std::vector<std::string> nodeNames = {"IntValue", "StringValue"};

    FileParse::deserializeOptionalVariant(adapter, nodeNames, optVar);

    ASSERT_TRUE(optVar.has_value());
    EXPECT_TRUE(std::holds_alternative<int>(optVar.value()));
    EXPECT_EQ(99, std::get<int>(optVar.value()));
}

//////////////////////////////////////////////////////////////////////////////
// VariantVector edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(VariantEdgeCases, SerializeVariantVectorIndexOutOfBounds)
{
    // Variant with vector<int> at index 1, but only provide 1 node name
    std::variant<std::vector<std::string>, std::vector<int>> v = std::vector<int>{1, 2, 3};

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"StringItem"};   // Only 1 name, but index is 1

    FileParse::serializeVariantVector(adapter, nodeNames, v);

    // No children should be added since index >= nodeNames.size()
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VariantEdgeCases, SerializeVariantVectorValid)
{
    std::variant<std::vector<std::string>, std::vector<int>> v =
      std::vector<std::string>{"a", "b", "c"};

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};
    FileParse::serializeVariantVector(adapter, nodeNames, v);

    EXPECT_EQ(3u, adapter.getNode().child.size());
}

TEST(VariantEdgeCases, DeserializeVariantVectorNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::variant<std::vector<std::string>, std::vector<int>> v;
    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};

    FileParse::deserializeVariantVector(adapter, nodeNames, v);

    // Should remain at default (empty vector<string>)
    EXPECT_TRUE(std::holds_alternative<std::vector<std::string>>(v));
}

TEST(VariantEdgeCases, DeserializeVariantVectorMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        Helper::addChildNode(node, "IntItem", "1");
        Helper::addChildNode(node, "IntItem", "2");
        Helper::addChildNode(node, "IntItem", "3");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::variant<std::vector<std::string>, std::vector<int>> v;
    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};

    FileParse::deserializeVariantVector(adapter, nodeNames, v);

    ASSERT_TRUE(std::holds_alternative<std::vector<int>>(v));
    const auto & vec = std::get<std::vector<int>>(v);
    ASSERT_EQ(3u, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
}

TEST(VariantEdgeCases, SerializeOptionalVariantVectorEmpty)
{
    std::optional<std::variant<std::vector<std::string>, std::vector<int>>> optVar = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};
    FileParse::serializeOptionalVariantVector(adapter, nodeNames, optVar);

    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VariantEdgeCases, DeserializeOptionalVariantVectorNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::variant<std::vector<std::string>, std::vector<int>>> optVar;
    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};

    FileParse::deserializeOptionalVariantVector(adapter, nodeNames, optVar);

    EXPECT_FALSE(optVar.has_value());
}

TEST(VariantEdgeCases, DeserializeOptionalVariantVectorMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        Helper::addChildNode(node, "StringItem", "x");
        Helper::addChildNode(node, "StringItem", "y");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::variant<std::vector<std::string>, std::vector<int>>> optVar;
    std::vector<std::string> nodeNames = {"StringItem", "IntItem"};

    FileParse::deserializeOptionalVariantVector(adapter, nodeNames, optVar);

    ASSERT_TRUE(optVar.has_value());
    EXPECT_TRUE(std::holds_alternative<std::vector<std::string>>(optVar.value()));
}
