
#ifndef FILEMANAGEMENTSYSTEM_TREENODE_H
#define FILEMANAGEMENTSYSTEM_TREENODE_H


#include <string>
#include <utility>
#include <vector>

/*
 * A simple regular tree dataStructure implementation.
 * It has nothing to do with the file management system
 * */

struct TreeNode {
    std::string name;
    std::vector<TreeNode*> children;

    explicit TreeNode(std::string  name) : name(std::move(name)) {}

    void addChild(TreeNode* child) {
        children.push_back(child);
    }
};


#endif //FILEMANAGEMENTSYSTEM_TREENODE_H
