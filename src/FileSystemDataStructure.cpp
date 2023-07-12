
#include "FileSystemDataStructure.h"


/** FileSystemDataStructure::Node Constructors **/

FileSystemDataStructure::Node::Node(std::string &name, bool file) {
    this->name = name;
    this->file = file;
}

FileSystemDataStructure::Node::Node(std::string &name, FileSystemDataStructure::Node *Parent, bool isFile) {
    this->name = name;
    this->file = isFile;
}

/** FileSystemDataStructure::Node Constant Methods **/

bool FileSystemDataStructure::Node::isFile() const { return file; }

FileSystemDataStructure::Node* FileSystemDataStructure::Node::getParent() const { return parent; }

std::vector<FileSystemDataStructure::Node *> FileSystemDataStructure::Node::getChildren() const {
    return children;
}

/** FileSystemDataStructure::Node Non-Constant Methods **/

/*
 * Add a child node
 *
 * @param child Pointer to child node to be added
 * */
void FileSystemDataStructure::Node::addChild(FileSystemDataStructure::Node *child) {
    children.push_back(child);
}

/*
 * Remove a child node from the current node.
 *
 * @param child Pointer to the child node to be removed.
 * @return True if the child node was found and removed successfully, False otherwise.
 */
bool FileSystemDataStructure::Node::removeChild(FileSystemDataStructure::Node *child) {
    for (auto it=children.begin(); it != children.end() ; ++it) {
        const auto element = *it;

        // child to be removed found
        if(element == child) {
            children.erase(it);
            return true;
        }
    }

    // node to be removed isn't a child of this node
    return false;
}

/*
 * Set the node of the Current Node
 * @param node Pointer to the parent node
 * */
void FileSystemDataStructure::Node::setParent(FileSystemDataStructure::Node *node) {
    parent = node;
}

