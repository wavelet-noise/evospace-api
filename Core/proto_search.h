#pragma once

#include <memory>
#include <unordered_map>

class UPrototype;

template <typename T> class TextTrie {
  public:
    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        bool isLeaf = false;
        T value;
    };

    void insert(const std::string &key, T value) {
        auto node = &root;
        for (char c : key) {
            auto childIt = node->children.find(c);
            if (childIt == node->children.end()) {
                node->children[c] = std::make_unique<TrieNode>();
            }
            node = node->children[c].get();
        }
        node->isLeaf = true;
        node->value = std::move(value);
    }

    std::vector<const T *> search(const std::string &key) const {
        std::vector<const T *> results;
        auto node = findNode(key);
        if (node) {
            collectLeaves(node, results);
        }
        return results;
    }

  private:
    TrieNode root;

    TrieNode *findNode(const std::string &key) const {
        auto node = &root;
        for (char c : key) {
            auto childIt = node->children.find(c);
            if (childIt == node->children.end()) {
                return nullptr;
            }
            node = childIt->second.get();
        }
        return node;
    }

    void
    collectLeaves(const TrieNode *node, std::vector<const T *> &results) const {
        if (node->isLeaf) {
            results.push_back(&node->value);
        }
        for (const auto &child : node->children) {
            collectLeaves(child.second.get(), results);
        }
    }
};

using PrototypeSearch = TextTrie<UPrototype *>;
