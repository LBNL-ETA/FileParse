#include <utility>
#include <algorithm>

#include "MockNodeAdapter.hxx"

namespace Helper
{

    MockNodeAdapter::MockNodeAdapter(MockNode * node) : node_(node)
    {}

    MockNode::MockNode(std::string tag) : tag(std::move(tag))
    {}

    bool MockNodeAdapter::isEmpty() const
    {
        return node_ == nullptr || (node_->child.empty() && node_->text.empty());
    }

    std::string MockNodeAdapter::getCurrentTag() const
    {
        return node_->tag;
    }

    bool MockNodeAdapter::isCurrentTag(std::string_view name) const
    {
        return name.data() == node_->tag;
    }

    int MockNodeAdapter::nChildNode() const
    {
        return static_cast<int>(node_->child.size());
    }

    MockNodeAdapter MockNodeAdapter::getChildNode(int i) const
    {
        if(i < node_->child.size())
        {
            return MockNodeAdapter(&node_->child[i]);
        }

        return MockNodeAdapter(nullptr);
    }

    MockNodeAdapter MockNodeAdapter::getChildNode(std::string_view name, int i) const
    {
        int count = 0;
        for(auto & child : node_->child)
        {
            if(child.tag == name)
            {
                if(count == i)
                {
                    return MockNodeAdapter(&child);
                }
                count++;
            }
        }
        return MockNodeAdapter(
          nullptr);   // Return an empty MockNodeAdapter if no matching child is found
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
}