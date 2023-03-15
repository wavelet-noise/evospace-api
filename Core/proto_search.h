#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class UPrototype;

class TrieNode {
public:
    bool isLeaf;
    std::unordered_map<char, TrieNode*> children;

    TrieNode() : isLeaf(false) {}
};

struct SearchResult {
    std::string text;
    const TrieNode* node;
};

class ProtoSearch {
public:
    void add_proto(const std::string& text, const UPrototype * proto) {
        // Add the text to the trie
        insert(text);
        texts.push_back(text);
    }

    std::vector<SearchResult> search(std::string_view searchTerm) const {
        std::vector<SearchResult> results;

        // Find the node in the trie that corresponds to the search term
        auto node = findNode(searchTerm.data());

        // If there is no node that matches the search term, return an empty vector
        if (!node) {
            return results;
        }

        // Collect all of the leaf nodes below the search node
        collectLeaves(node, results);

        // Remove duplicates from the results vector
        std::sort(results.begin(), results.end(),
                  [](const SearchResult& a, const SearchResult& b) {
                      return a.node < b.node;
                  });
        results.erase(std::unique(results.begin(), results.end(),
                                  [](const SearchResult& a, const SearchResult& b) {
                                      return a.node == b.node;
                                  }),
                       results.end());

        return results;
    }

private:
    TrieNode root;
    std::vector<std::string> texts;

    void insert(const std::string& key, const UPrototype * proto) {
        auto node = &root;
        for (char c : key) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isLeaf = true;
    }

    const TrieNode *findNode(const std::string &key) const {
        auto node = &root;
        auto keyIt = key.begin();
        while (keyIt != key.end()) {
            // Convert the character to lowercase
            char c = std::tolower(*keyIt);
            auto childIt = node->children.find(c);
            if (childIt == node->children.end()) {
                // If the character is not found, try to match it against the other characters in the node's keys
                bool found = false;
                for (auto& child : node->children) {
                    if (std::tolower(child.first) == c) {
                        node = child.second;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    return nullptr;
                }
            } else {
                node = childIt->second;
                ++keyIt;
            }
        }
        return node;
    }

    void collectLeaves(const TrieNode* node, std::vector<SearchResult>& results) const {
        if (node->isLeaf) {
            results.push_back({texts[std::distance(&root, node)], node});
        }
        for (auto& child : node->children) {
            collectLeaves(child.second, results);
        }
    }
};