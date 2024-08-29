#include <utility>
#include <algorithm>
#include <iterator>

#include "MockNodeAdapter.hxx"

namespace Helper
{

    MockNodeAdapter::MockNodeAdapter(MockNode * node) : node_(node)
    {}

    MockNode::MockNode(std::string tag) : tag(std::move(tag))
    {}

    MockNode & MockNode::addChild(const std::string & tagName)
    {
        // add child
        child.emplace_back(tagName);
        return child.back();
    }

    void MockNode::addAttribute(std::string_view name, std::string_view value)
    {
        attributes_[name.data()] = value.data();
    }

    std::optional<std::string> MockNode::getAttribute(std::string_view name) const
    {
        if(auto it = attributes_.find(name.data()); it != attributes_.end())
        {
            return it->second;
        }
        return std::nullopt;
    }

    bool MockNodeAdapter::isEmpty() const
    {
        return node_ == nullptr || (node_->child.empty() && node_->text.empty());
    }

    std::string MockNodeAdapter::getCurrentTag() const
    {
        return node_->tag;
    }

    std::vector<MockNodeAdapter> MockNodeAdapter::getChildNodes() const
    {
        std::vector<MockNodeAdapter> children;
        children.reserve(node_->child.size());

        std::transform(begin(node_->child),
                       end(node_->child),
                       std::back_inserter(children),
                       [](auto & child) { return MockNodeAdapter(&child); });

        return children;
    }

    std::optional<MockNodeAdapter> MockNodeAdapter::getFirstChildByName(std::string_view name) const
    {
        for(auto & child : node_->child)
        {
            if(child.tag == name)
            {
                return MockNodeAdapter(&child);
            }
        }

        return std::nullopt;
    }

    std::vector<MockNodeAdapter> MockNodeAdapter::getChildNodesByName(std::string_view name) const
    {
        std::vector<MockNodeAdapter> children;
        children.reserve(nChildNode(name));

        for(int i = 0; i < node_->child.size(); ++i)
        {
            if(node_->child[i].tag == name)
            {
                children.emplace_back(&node_->child[i]);
            }
        }

        return children;
    }

    int MockNodeAdapter::nChildNode(std::string_view name) const
    {
        return static_cast<int>(
          std::count_if(node_->child.begin(), node_->child.end(), [&name](const auto & child) {
              return child.tag == name;
          }));
    }

    bool MockNodeAdapter::hasChildNode(std::string_view name) const
    {
        return nChildNode(name) > 0;
    }

    std::string MockNodeAdapter::getText() const
    {
        return node_->text;
    }

    MockNodeAdapter MockNodeAdapter::addChild(std::string_view name)
    {
        return MockNodeAdapter(&node_->addChild(name.data()));
    }

    void MockNodeAdapter::addText(std::string_view text)
    {
        node_->text = text.data();
    }

    MockNode MockNodeAdapter::getNode() const
    {
        return *node_;
    }

    // Not implemented yet since it is not used
    std::string MockNodeAdapter::getContent() const
    {
        return "";
    }

    void MockNodeAdapter::addAttribute(std::string_view name, std::string_view value)
    {
        if(node_ != nullptr)
        {
            node_->addAttribute(name, value);
        }
    }

    std::optional<std::string> MockNodeAdapter::getAttribute(std::string_view name) const
    {
        if(node_ != nullptr)
        {
            return node_->getAttribute(name);
        }

        return std::nullopt;
    }

    MockNode & addChildNode(MockNode & parentNode, std::string_view tag, std::string_view text)
    {
        MockNode node;
        node.tag = tag;
        node.text = text;

        parentNode.child.push_back(node);

        return parentNode.child.back();
    }

    MockNode & addChildNode(MockNode & parentNode, std::string_view tag, MockNode childNode)
    {
        childNode.tag = tag;

        parentNode.child.push_back(childNode);

        return parentNode.child.back();
    }

    bool compareNodes(const MockNode & node1, const MockNode & node2)
    {
        if(node1.tag != node2.tag || node1.text != node2.text)
        {
            return false;
        }
        if(node1.child.size() != node2.child.size())
        {
            return false;
        }
        for(size_t i = 0; i < node1.child.size(); ++i)
        {
            if(!compareNodes(node1.child[i], node2.child[i]))
            {
                return false;
            }
        }
        return true;
    }
}   // namespace Helper