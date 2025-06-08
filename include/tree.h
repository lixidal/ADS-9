// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

struct TreeNode {
    char element;
    std::unique_ptr<TreeNode[]> branches;
    unsigned branchCount;

    TreeNode(char e, unsigned bc) : element(e), branchCount(bc) {
        branches.reset(new TreeNode[bc]);
    };
};

class PMTree {
private:
    std::unique_ptr<TreeNode> root;

    void grow(TreeNode* node, const std::vector<char>& elements);
    bool generate_path(TreeNode* node, std::vector<char>& buffer, std::vector<std::vector<char>>& result);
    std::vector<char> locate_permutation(TreeNode* node, int pos);

public:
    PMTree(const std::vector<char>& input_data);
    ~PMTree() = default;

    std::vector<std::vector<char>> extract_all_permutations();
    std::vector<char> obtain_permutation_at(int number);
};

#endif  // INCLUDE_TREE_H_
