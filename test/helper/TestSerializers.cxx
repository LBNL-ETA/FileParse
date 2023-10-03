#include "TestSerializers.hxx"

XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::BaseElement & base)
{
    xmlNode >> Child("SampleText", base.text);
    return xmlNode;
}

XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::BaseElement & base)
{
    xmlNode << Child("SampleText", base.text);
    return xmlNode;
}

namespace Helper
{
    BaseElement loadBaseElement(std::string_view fileName)
    {
        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        BaseElement base;
        xmlNode >> Child{"BaseElement", base};

        return base;
    }
}   // namespace Helper