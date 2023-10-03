#pragma once

#include "TestStructures.hxx"

#include "XMLNodeAdapter.hxx"
#include "xmlParser.h"

#include "CommonSerializer.hxx"

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::BaseElement & base);
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::BaseElement & base);

namespace Helper
{
    BaseElement loadBaseElement(std::string_view fileName);
}   // namespace Helper