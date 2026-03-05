#pragma once

#include "fileParse/Common.hxx"
#include "fileParse/Optional.hxx"
#include "fileParse/Vector.hxx"

#include "test/helper/structures/StructureLanguages.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, LanguageEntry & entry)
    {
        using FileParse::Child;
        node >> Child{"Language", entry.language};
        node >> Child{"Text", entry.text};
        node >> Child{"OptionalText", entry.optional_text};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const LanguageEntry & entry)
    {
        using FileParse::Child;
        node << Child{"Language", entry.language};
        node << Child{"Text", entry.text};
        node << Child{"OptionalText", entry.optional_text};
        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, LanguageCollection & collection)
    {
        using FileParse::Child;
        node >> Child{{"Entries", "Entry"}, collection.entries};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const LanguageCollection & collection)
    {
        using FileParse::Child;
        node << Child{{"Entries", "Entry"}, collection.entries};
        return node;
    }
}   // namespace Helper
