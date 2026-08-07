#include "JSONNodeAdapter.hxx"

#include <nlohmann/json.hpp>

#include <fstream>

JSONNodeAdapter::JSONNodeAdapter(nlohmann::json * jsonPtr, std::string key)
    : jsonPtr_(jsonPtr), key_(std::move(key))
{}

JSONNodeAdapter::JSONNodeAdapter(std::shared_ptr<nlohmann::json> ownedJson, std::string key)
    : ownedJson_(std::move(ownedJson)), jsonPtr_(ownedJson_.get()), key_(std::move(key))
{}

bool JSONNodeAdapter::isEmpty() const
{
    return jsonPtr_ == nullptr || jsonPtr_->is_null();
}

std::string JSONNodeAdapter::getCurrentTag() const
{
    return key_;
}

std::string JSONNodeAdapter::getText() const
{
    if(jsonPtr_ == nullptr)
    {
        return {};
    }

    const auto & json = *jsonPtr_;

    if(json.is_string())
    {
        return json.get<std::string>();
    }
    if(json.is_number_integer())
    {
        return std::to_string(json.get<int64_t>());
    }
    if(json.is_number_unsigned())
    {
        return std::to_string(json.get<uint64_t>());
    }
    if(json.is_number_float())
    {
        return std::to_string(json.get<double>());
    }
    if(json.is_boolean())
    {
        return json.get<bool>() ? "true" : "false";
    }

    return {};
}

std::vector<JSONNodeAdapter> JSONNodeAdapter::getChildNodes() const
{
    std::vector<JSONNodeAdapter> children;

    if(jsonPtr_ == nullptr)
    {
        return children;
    }

    const auto & json = *jsonPtr_;

    if(json.is_object())
    {
        for(auto it = json.begin(); it != json.end(); ++it)
        {
            // For arrays, create a child for each element
            if(it.value().is_array())
            {
                for(size_t i = 0; i < it.value().size(); ++i)
                {
                    children.emplace_back(
                      const_cast<nlohmann::json *>(&((*jsonPtr_)[it.key()][i])), it.key());
                }
            }
            else
            {
                children.emplace_back(
                  const_cast<nlohmann::json *>(&((*jsonPtr_)[it.key()])), it.key());
            }
        }
    }
    else if(json.is_array())
    {
        for(size_t i = 0; i < json.size(); ++i)
        {
            children.emplace_back(const_cast<nlohmann::json *>(&((*jsonPtr_)[i])),
                                  key_);
        }
    }

    return children;
}

std::optional<JSONNodeAdapter> JSONNodeAdapter::getFirstChildByName(std::string_view name) const
{
    if(jsonPtr_ == nullptr || !jsonPtr_->is_object())
    {
        return std::nullopt;
    }

    const std::string nameStr(name);
    if(jsonPtr_->contains(nameStr))
    {
        auto & child = (*jsonPtr_)[nameStr];
        if(child.is_array() && !child.empty())
        {
            return JSONNodeAdapter(&child[0], nameStr);
        }
        return JSONNodeAdapter(&child, nameStr);
    }

    return std::nullopt;
}

std::vector<JSONNodeAdapter> JSONNodeAdapter::getChildNodesByName(std::string_view name) const
{
    std::vector<JSONNodeAdapter> children;

    if(jsonPtr_ == nullptr || !jsonPtr_->is_object())
    {
        return children;
    }

    const std::string nameStr(name);
    if(jsonPtr_->contains(nameStr))
    {
        auto & child = (*jsonPtr_)[nameStr];
        if(child.is_array())
        {
            for(size_t i = 0; i < child.size(); ++i)
            {
                children.emplace_back(&child[i], nameStr);
            }
        }
        else
        {
            children.emplace_back(&child, nameStr);
        }
    }

    return children;
}

int JSONNodeAdapter::nChildNode(std::string_view name) const
{
    if(jsonPtr_ == nullptr || !jsonPtr_->is_object())
    {
        return 0;
    }

    const std::string nameStr(name);
    if(jsonPtr_->contains(nameStr))
    {
        const auto & child = (*jsonPtr_)[nameStr];
        if(child.is_array())
        {
            return static_cast<int>(child.size());
        }
        return 1;
    }

    return 0;
}

bool JSONNodeAdapter::hasChildNode(std::string_view name) const
{
    if(jsonPtr_ == nullptr || !jsonPtr_->is_object())
    {
        return false;
    }

    return jsonPtr_->contains(std::string(name));
}

JSONNodeAdapter JSONNodeAdapter::addChild(std::string_view name)
{
    if(jsonPtr_ == nullptr)
    {
        return JSONNodeAdapter(nullptr, std::string(name));
    }

    // Ensure the current node is an object
    if(!jsonPtr_->is_object())
    {
        *jsonPtr_ = nlohmann::json::object();
    }

    const std::string nameStr(name);

    // If child doesn't exist, create it as an object
    if(!jsonPtr_->contains(nameStr))
    {
        (*jsonPtr_)[nameStr] = nlohmann::json::object();
        return JSONNodeAdapter(&(*jsonPtr_)[nameStr], nameStr);
    }

    // Child exists - convert to array or append to existing array
    auto & existing = (*jsonPtr_)[nameStr];
    if(!existing.is_array())
    {
        // Convert existing value to array
        nlohmann::json arr = nlohmann::json::array();
        arr.push_back(std::move(existing));
        arr.push_back(nlohmann::json::object());
        (*jsonPtr_)[nameStr] = std::move(arr);
        return JSONNodeAdapter(&(*jsonPtr_)[nameStr].back(), nameStr);
    }

    // Already an array, append new object
    existing.push_back(nlohmann::json::object());
    return JSONNodeAdapter(&existing.back(), nameStr);
}

void JSONNodeAdapter::addText(std::string_view text)
{
    if(jsonPtr_ == nullptr)
    {
        return;
    }

    *jsonPtr_ = std::string(text);
}

int JSONNodeAdapter::writeToFile(std::string_view fileName) const
{
    if(jsonPtr_ == nullptr)
    {
        return 1;
    }

    const std::string fileNameStr{fileName};
    std::ofstream file{fileNameStr};
    if(!file.is_open())
    {
        return 1;
    }

    // If this is a root node with ownership, write the owned JSON
    // Otherwise, wrap in an object with the key if it has one
    if(ownedJson_)
    {
        file << ownedJson_->dump(4);
    }
    else if(!key_.empty())
    {
        nlohmann::json wrapper;
        wrapper[key_] = *jsonPtr_;
        file << wrapper.dump(4);
    }
    else
    {
        file << jsonPtr_->dump(4);
    }

    return 0;
}

std::string JSONNodeAdapter::getContent() const
{
    if(jsonPtr_ == nullptr)
    {
        return {};
    }

    // If this is a root node with ownership, return the owned JSON
    if(ownedJson_)
    {
        return ownedJson_->dump(4);
    }

    // Otherwise, wrap in an object with the key if it has one
    if(!key_.empty())
    {
        nlohmann::json wrapper;
        wrapper[key_] = *jsonPtr_;
        return wrapper.dump(4);
    }

    return jsonPtr_->dump(4);
}

void JSONNodeAdapter::addAttribute(std::string_view name, std::string_view value)
{
    if(jsonPtr_ == nullptr)
    {
        return;
    }

    // Ensure the current node is an object
    if(!jsonPtr_->is_object())
    {
        *jsonPtr_ = nlohmann::json::object();
    }

    // Store attribute with @ prefix to distinguish from child nodes
    (*jsonPtr_)["@" + std::string(name)] = std::string(value);
}

std::optional<std::string> JSONNodeAdapter::getAttribute(std::string_view name) const
{
    if(jsonPtr_ == nullptr || !jsonPtr_->is_object())
    {
        return std::nullopt;
    }

    // Look for attribute with @ prefix
    const std::string nameStr = "@" + std::string(name);
    if(jsonPtr_->contains(nameStr))
    {
        const auto & val = (*jsonPtr_)[nameStr];
        if(val.is_string())
        {
            return val.get<std::string>();
        }
        if(val.is_number_integer())
        {
            return std::to_string(val.get<int64_t>());
        }
        if(val.is_number_unsigned())
        {
            return std::to_string(val.get<uint64_t>());
        }
        if(val.is_number_float())
        {
            return std::to_string(val.get<double>());
        }
        if(val.is_boolean())
        {
            return val.get<bool>() ? "true" : "false";
        }
    }

    return std::nullopt;
}

JSONNodeAdapter createJSONTopNode(std::string_view topNodeName)
{
    auto root = std::make_shared<nlohmann::json>(nlohmann::json::object());
    const std::string topNodeStr(topNodeName);
    (*root)[topNodeStr] = nlohmann::json::object();

    // Create adapter for the inner node (the actual top node)
    JSONNodeAdapter adapter(root, topNodeStr);
    adapter.jsonPtr_ = &(*root)[topNodeStr];

    return adapter;
}

std::optional<JSONNodeAdapter> getJSONTopNodeFromFile(std::string_view fileName,
                                                       std::string_view topNodeName)
{
    try
    {
        const std::string fileNameStr{fileName};
        std::ifstream file{fileNameStr};
        if(!file.is_open())
        {
            return std::nullopt;
        }

        auto root = std::make_shared<nlohmann::json>();
        file >> *root;

        const std::string topNodeStr(topNodeName);
        if(!root->is_object() || !root->contains(topNodeStr))
        {
            return std::nullopt;
        }

        JSONNodeAdapter adapter(root, topNodeStr);
        adapter.jsonPtr_ = &(*root)[topNodeStr];

        return adapter;
    }
    catch(const std::exception &)
    {
        return std::nullopt;
    }
}

std::optional<JSONNodeAdapter> getJSONTopNodeFromString(std::string_view json,
                                                         std::string_view topNodeName)
{
    try
    {
        auto root = std::make_shared<nlohmann::json>(nlohmann::json::parse(json));

        const std::string topNodeStr(topNodeName);
        if(!root->is_object() || !root->contains(topNodeStr))
        {
            return std::nullopt;
        }

        JSONNodeAdapter adapter(root, topNodeStr);
        adapter.jsonPtr_ = &(*root)[topNodeStr];

        return adapter;
    }
    catch(const std::exception &)
    {
        return std::nullopt;
    }
}
