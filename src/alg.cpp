// Copyright 2022 NNTU-CS
#include <iostream>
#include <algorithm>
#include <vector>
#include "tree.h"

TreeNode::TreeNode(char d) : data(d) {}

TreeNode::~TreeNode() {
    for (auto descendant : descendants)
        delete descendant;
}
PMTree::PMTree(const std::vector<char>& input_chars) {
    root_node = new TreeNode(' ');
    construct_tree(root_node, input_chars);
}
PMTree::~PMTree() {
    delete root_node;
}

void PMTree::construct_tree(TreeNode* node, std::vector<char> remainder) {
    std::sort(remainder.begin(), remainder.end());
    for (char ch : remainder) {
        TreeNode* child = new TreeNode(ch);
        node->descendants.push_back(child);
        std::vector<char> next(remainder);
        next.erase(std::remove(next.begin(), next.end(), ch), next.end());
        construct_tree(child, next);
    }
}
void PMTree::search_paths(TreeNode* node, std::vector<char>& current_path,
                         std::vector<std::vector<char>>& paths) {
    if (node->data != ' ')
        current_path.push_back(node->data);
    if (node->descendants.empty()) {
        paths.push_back(current_path);
    } else {
        for (auto descendant : node->descendants)
            search_paths(descendant, current_path, paths);
    }
    if (!current_path.empty() && node->data != ' ')
        current_path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> all_permutations;
    std::vector<char> path;
    tree.search_paths(tree.root_node, path, all_permutations);
    return all_permutations;
}
std::vector<char> getPerm1(PMTree& tree, int position) {
    auto full_permutations = getAllPerms(tree);
    return (position > 0 && position <= full_permutations.size()) ?
           full_permutations[position - 1] : std::vector<char>();
}
std::vector<char> PMTree::find_by_order(TreeNode* node, int& current_count,
                                       int target_position) {
    if (node->descendants.empty()) {
        ++current_count;
        return (current_count == target_position) ?
               std::vector<char>{node->data} : std::vector<char>{};
    }
    for (auto descendant : node->descendants) {
        auto found_perm = find_by_order(descendant, current_count,
                                       target_position);
        if (!found_perm.empty()) {
            if (node->data != ' ')
                found_perm.insert(found_perm.begin(), node->data);
            return found_perm;
        }
    }
    return {};
}
std::vector<char> getPerm2(PMTree& tree, int position) {
    int current_count = 0;
    return tree.find_by_order(tree.root_node, current_count, position);
}
