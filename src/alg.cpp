// Copyright 2022 NNTU-CS
#include <iostream>
#include <algorithm>
#include <vector>
#include "tree.h"

void PMTree::grow(TreeNode* node, const std::vector<char>& elements) {
    std::sort(elements.begin(), elements.end());
    for (unsigned i = 0; i < elements.size(); ++i) {
        char current_element = elements[i];
        std::vector<char> next_elements(elements.begin(), elements.end());
        next_elements.erase(std::remove(next_elements.begin(), next_elements.end(), current_element), next_elements.end());
        node->branches[i].element = current_element;
        node->branchCount--;
        grow(&node->branches[i], next_elements);
    }
}

bool PMTree::generate_path(TreeNode* node, std::vector<char>& path_buffer, std::vector<std::vector<char>>& result) {
    if (node->branchCount == 0) {
        path_buffer.push_back(node->element);
        result.emplace_back(path_buffer);
        path_buffer.pop_back();
        return true;
    }
    path_buffer.push_back(node->element);
    for (unsigned i = 0; i < node->branchCount; ++i) {
        generate_path(&node->branches[i], path_buffer, result);
    }
    path_buffer.pop_back();
    return false;
}

std::vector<char> PMTree::locate_permutation(TreeNode* node, int pos) {
    std::vector<char> buffer;
    buffer.reserve(pos + 1);
    while (pos--) {
        buffer.push_back(node->element);
        node = &node->branches[pos % node->branchCount];
    }
    buffer.push_back(node->element);
    return buffer;
}

PMTree::PMTree(const std::vector<char>& input_data) {
    root = std::make_unique<TreeNode>(' ', input_data.size());
    grow(root.get(), input_data);
}

std::vector<std::vector<char>> PMTree::extract_all_permutations() {
    std::vector<std::vector<char>> result;
    std::vector<char> path_buffer;
    generate_path(root.get(), path_buffer, result);
    return result;
}

std::vector<char> PMTree::obtain_permutation_at(int number) {
    if (number <= 0 || number > factorials(input_data.size())) return {};
    return locate_permutation(root.get(), number - 1);
}
