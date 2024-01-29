#include <gtest/gtest.h>

#include "test/helper/files/BaseElementXML.hxx"
#include "test/helper/structures/StructureBase.hxx"
#include "test/helper/serializers/SerializersBaseElement.hxx"

#include "test/helper/MockNodeAdapter.hxx"

Helper::MockNode createBaseElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "SampleText", "TestText");
    addChildNode(node, "OptionalText", "OptionalText");
    addChildNode(node, "Integer", "13");
    addChildNode(node, "OptionalInteger", "23");
    addChildNode(node, "Double", "3.1415926");
    addChildNode(node, "Size_t", "18");
    addChildNode(node, "Boolean", "true");
    addChildNode(node, "OptionalDouble", "4.1415926");
    addChildNode(node, "OptionalBoolean", "false");
    addChildNode(node, "VariantString", "VariantText");
    addChildNode(node, "VariantString1", "VariantText1");

    return node;
}

class BaseSerializerTest : public testing::Test
{};

///////////////////////////////////////////
/// Text field
///////////////////////////////////////////

Helper::MockNode createTextElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "SampleText", "TestText");

    return node;
}

TEST_F(BaseSerializerTest, DeserializeText)
{
    auto elementNode(createTextElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::TextElement element;
    adapter >> element;

    EXPECT_EQ("TestText", element.text);
}

TEST_F(BaseSerializerTest, SerializeText)
{
    Helper::TextElement element;
    element.text = "Text to test";

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Integer field
///////////////////////////////////////////

Helper::MockNode createIntegerElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "Integer", "81");

    return node;
}

TEST_F(BaseSerializerTest, DeserializeInteger)
{
    auto elementNode(createIntegerElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::IntegerNumberElement element;
    adapter >> element;

    EXPECT_EQ(81, element.integer_number);
}

TEST_F(BaseSerializerTest, SerializeInteger)
{
    Helper::IntegerNumberElement element;
    element.integer_number = 123;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Optional Integer field
///////////////////////////////////////////

Helper::MockNode createOptionalIntegerElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "OptionalInteger", "91");

    return node;
}

// Optional field is missing. It should be nullopt in the test
Helper::MockNode createOptionalIntegerEmptyElement()
{
    Helper::MockNode node{"BaseElement"};

    return node;
}

TEST_F(BaseSerializerTest, DeserializeOptionalInteger)
{
    auto elementNode(createOptionalIntegerElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalIntegerElement element;
    adapter >> element;

    EXPECT_EQ(91, element.optional_int);
}

TEST_F(BaseSerializerTest, DeserializeOptionalIntegerEmpty)
{
    auto elementNode(createOptionalIntegerEmptyElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalIntegerElement element;
    adapter >> element;

    EXPECT_EQ(false, element.optional_int.has_value());
}

TEST_F(BaseSerializerTest, SerializeOptionalInteger)
{
    Helper::OptionalIntegerElement element;
    element.optional_int = 314;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalIntegerEmpty)
{
    Helper::OptionalIntegerElement element;
    element.optional_int = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Double field
///////////////////////////////////////////

Helper::MockNode createDoubleElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "Double", "42.5");

    return node;
}

TEST_F(BaseSerializerTest, DeserializeDouble)
{
    auto elementNode(createDoubleElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::DoubleNumberElement element;
    adapter >> element;

    EXPECT_DOUBLE_EQ(42.5, element.double_number);
}

TEST_F(BaseSerializerTest, SerializeDouble)
{
    Helper::DoubleNumberElement element;
    element.double_number = 99.9;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Optional Double field
///////////////////////////////////////////

Helper::MockNode createOptionalDoubleElement()
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "OptionalDouble", "45.67");

    return node;
}

// Optional field is missing. It should be nullopt in the test
Helper::MockNode createOptionalDoubleEmptyElement()
{
    Helper::MockNode node{"BaseElement"};

    return node;
}

TEST_F(BaseSerializerTest, DeserializeOptionalDouble)
{
    auto elementNode(createOptionalDoubleElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalDoubleElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_double.has_value());
    EXPECT_DOUBLE_EQ(45.67, element.optional_double.value());
}

TEST_F(BaseSerializerTest, DeserializeOptionalDoubleEmpty)
{
    auto elementNode(createOptionalDoubleEmptyElement());
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalDoubleElement element;
    adapter >> element;

    EXPECT_EQ(false, element.optional_double.has_value());
}

TEST_F(BaseSerializerTest, SerializeOptionalDouble)
{
    Helper::OptionalDoubleElement element;
    element.optional_double = 123.45;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalDoubleEmpty)
{
    Helper::OptionalDoubleElement element;
    element.optional_double = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Boolean field
///////////////////////////////////////////

Helper::MockNode createBooleanElement(bool value)
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "Boolean", value ? "true" : "false");

    return node;
}

TEST_F(BaseSerializerTest, DeserializeBooleanTrue)
{
    auto elementNode = createBooleanElement(true);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::BooleanFieldElement element;
    adapter >> element;

    EXPECT_TRUE(element.boolean_field);
}

TEST_F(BaseSerializerTest, DeserializeBooleanFalse)
{
    auto elementNode = createBooleanElement(false);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::BooleanFieldElement element;
    adapter >> element;

    EXPECT_FALSE(element.boolean_field);
}

TEST_F(BaseSerializerTest, SerializeBoolean)
{
    Helper::BooleanFieldElement element;
    element.boolean_field = false;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Optional Boolean field
///////////////////////////////////////////

Helper::MockNode createOptionalBooleanElement(const std::optional<bool>& value)
{
    Helper::MockNode node{"BaseElement"};
    if (value.has_value())
    {
        addChildNode(node, "OptionalBoolean", value.value() ? "true" : "false");
    }

    return node;
}

TEST_F(BaseSerializerTest, DeserializeOptionalBooleanTrue)
{
    auto elementNode = createOptionalBooleanElement(true);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalBooleanElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_boolean.has_value());
    EXPECT_TRUE(element.optional_boolean.value());
}

TEST_F(BaseSerializerTest, DeserializeOptionalBooleanFalse)
{
    auto elementNode = createOptionalBooleanElement(false);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalBooleanElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_boolean.has_value());
    EXPECT_FALSE(element.optional_boolean.value());
}

TEST_F(BaseSerializerTest, DeserializeOptionalBooleanEmpty)
{
    auto elementNode = createOptionalBooleanElement(std::nullopt);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalBooleanElement element;
    adapter >> element;

    EXPECT_EQ(false, element.optional_boolean.has_value());
}

TEST_F(BaseSerializerTest, SerializeOptionalBoolean)
{
    Helper::OptionalBooleanElement element;
    element.optional_boolean = true;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalBooleanEmpty)
{
    Helper::OptionalBooleanElement element;
    element.optional_boolean = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// SizeT field
///////////////////////////////////////////

Helper::MockNode createSizeTElement(size_t value)
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "Size_t", std::to_string(value));

    return node;
}

TEST_F(BaseSerializerTest, DeserializeSizeT)
{
    auto elementNode = createSizeTElement(12345u);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::SizeTFieldElement element;
    adapter >> element;

    EXPECT_EQ(12345u, element.size_t_field);
}

TEST_F(BaseSerializerTest, SerializeSizeT)
{
    Helper::SizeTFieldElement element;
    element.size_t_field = 67890u;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Optional SizeT field
///////////////////////////////////////////

Helper::MockNode createOptionalSizeTElement(const std::optional<size_t>& value)
{
    Helper::MockNode node{"BaseElement"};
    if (value.has_value())
    {
        addChildNode(node, "OptionalSize_t", std::to_string(value.value()));
    }

    return node;
}

TEST_F(BaseSerializerTest, DeserializeOptionalSizeT)
{
    auto elementNode = createOptionalSizeTElement(54321u);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalSizeTFieldElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_size_t_field.has_value());
    EXPECT_EQ(54321u, element.optional_size_t_field.value());
}

TEST_F(BaseSerializerTest, DeserializeOptionalSizeTEmpty)
{
    auto elementNode = createOptionalSizeTElement(std::nullopt);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalSizeTFieldElement element;
    adapter >> element;

    EXPECT_EQ(false, element.optional_size_t_field.has_value());
}

TEST_F(BaseSerializerTest, SerializeOptionalSizeT)
{
    Helper::OptionalSizeTFieldElement element;
    element.optional_size_t_field = 98765u;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalSizeTEmpty)
{
    Helper::OptionalSizeTFieldElement element;
    element.optional_size_t_field = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Variant Field (Double and String)
///////////////////////////////////////////

Helper::MockNode createVariantFieldElementAsDouble(double value)
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "Double", std::to_string(value));

    return node;
}

Helper::MockNode createVariantFieldElementAsString(const std::string& value)
{
    Helper::MockNode node{"BaseElement"};
    addChildNode(node, "String", value);

    return node;
}

TEST_F(BaseSerializerTest, DeserializeVariantFieldAsDouble)
{
    auto elementNode = createVariantFieldElementAsDouble(123.45);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::VariantFieldElement element;
    adapter >> element;

    ASSERT_TRUE(std::holds_alternative<double>(element.variant_field));
    EXPECT_DOUBLE_EQ(123.45, std::get<double>(element.variant_field));
}

TEST_F(BaseSerializerTest, DeserializeVariantFieldAsString)
{
    auto elementNode = createVariantFieldElementAsString("hello");
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::VariantFieldElement element;
    adapter >> element;

    ASSERT_TRUE(std::holds_alternative<std::string>(element.variant_field));
    EXPECT_EQ("hello", std::get<std::string>(element.variant_field));
}

TEST_F(BaseSerializerTest, SerializeVariantFieldAsDouble)
{
    Helper::VariantFieldElement element;
    element.variant_field = 678.90;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeVariantFieldAsString)
{
    Helper::VariantFieldElement element;
    element.variant_field = "world";

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Optional Variant field (String and Int)
///////////////////////////////////////////

Helper::MockNode createOptionalVariantFieldElementAsString(const std::optional<std::string>& value)
{
    Helper::MockNode node{"BaseElement"};
    if (value.has_value())
    {
        addChildNode(node, "VariantString", value.value());
    }

    return node;
}

Helper::MockNode createOptionalVariantFieldElementAsInt(const std::optional<int>& value)
{
    Helper::MockNode node{"BaseElement"};
    if (value.has_value())
    {
        addChildNode(node, "VariantInt", std::to_string(value.value()));
    }

    return node;
}

Helper::MockNode createOptionalVariantFieldElementEmpty()
{
    return Helper::MockNode{"BaseElement"};
}

TEST_F(BaseSerializerTest, DeserializeOptionalVariantFieldAsString)
{
    auto elementNode = createOptionalVariantFieldElementAsString("test");
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalVariantElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_variant.has_value());
    ASSERT_TRUE(std::holds_alternative<std::string>(element.optional_variant.value()));
    EXPECT_EQ("test", std::get<std::string>(element.optional_variant.value()));
}

TEST_F(BaseSerializerTest, DeserializeOptionalVariantFieldAsInt)
{
    auto elementNode = createOptionalVariantFieldElementAsInt(42);
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalVariantElement element;
    adapter >> element;

    ASSERT_TRUE(element.optional_variant.has_value());
    ASSERT_TRUE(std::holds_alternative<int>(element.optional_variant.value()));
    EXPECT_EQ(42, std::get<int>(element.optional_variant.value()));
}

TEST_F(BaseSerializerTest, DeserializeOptionalVariantFieldEmpty)
{
    auto elementNode = createOptionalVariantFieldElementEmpty();
    const Helper::MockNodeAdapter adapter{&elementNode};

    Helper::OptionalVariantElement element;
    adapter >> element;

    EXPECT_FALSE(element.optional_variant.has_value());
}

TEST_F(BaseSerializerTest, SerializeOptionalVariantFieldAsString)
{
    Helper::OptionalVariantElement element;
    element.optional_variant = "example";

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalVariantFieldAsInt)
{
    Helper::OptionalVariantElement element;
    element.optional_variant = 123;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

TEST_F(BaseSerializerTest, SerializeOptionalVariantFieldEmpty)
{
    Helper::OptionalVariantElement element;
    element.optional_variant = std::nullopt;

    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};
    adapter << element;

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), elementNode));
}

///////////////////////////////////////////
/// Base element test
///////////////////////////////////////////

TEST_F(BaseSerializerTest, Reading)
{
    auto baseElementNode{createBaseElement()};
    const Helper::MockNodeAdapter adapter{&baseElementNode};

    Helper::BaseElement base;
    adapter >> base;

    EXPECT_EQ("TestText", base.text);
    EXPECT_EQ(13, base.integer_number);
    EXPECT_NEAR(3.1415926, base.double_number, 1e-6);
    EXPECT_EQ(true, base.boolean_field);
    EXPECT_EQ("OptionalText", base.optional_text);
    EXPECT_EQ(23, base.optional_int);
    EXPECT_EQ(18u, base.size_t_field);
    ASSERT_EQ(true, base.optional_double.has_value());
    EXPECT_NEAR(4.1415926, base.optional_double.value(), 1e-6);
    ASSERT_EQ(true, base.boolean_optional.has_value());
    if(base.boolean_optional.has_value())
    {
        EXPECT_EQ(false, base.boolean_optional.value());
    }
    if(auto str_ptr = std::get_if<std::string>(&base.variant_field))
    {
        EXPECT_EQ("VariantText", *str_ptr);
    }
    else
    {
        std::cerr << "variant_field does not hold a string value" << std::endl;
        FAIL();
    }

    ASSERT_EQ(true, base.optional_variant.has_value());
    if(auto str_ptr = std::get_if<std::string>(&base.optional_variant.value()))
    {
        EXPECT_EQ("VariantText1", *str_ptr);
    }
    else
    {
        std::cerr << "optional_variant_field does not hold a string value" << std::endl;
        FAIL();
    }
}