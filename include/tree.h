// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class TreeNode {
 public:
    char data;
    std::vector<TreeNode*> descendants;

    explicit TreeNode(char d);
    ~TreeNode();
};

class PMTree {
 private:
    TreeNode* root_node;

    void construct_tree(TreeNode* node, std::vector<char> remaining);
    void search_paths(TreeNode* node, std::vector<char>& path,
                     std::vector<std::vector<char>>& result);
    std::vector<char> find_by_order(TreeNode* node, int& count,
                                  int target_idx);

 public:
    explicit PMTree(const std::vector<char>& input_chars);
    ~PMTree();

    friend std::vector<std::vector<char>> getAllPerms(PMTree&);
    friend std::vector<char> getPerm1(PMTree&, int);
    friend std::vector<char> getPerm2(PMTree&, int);
};

#endif  // INCLUDE_TREE_H_
