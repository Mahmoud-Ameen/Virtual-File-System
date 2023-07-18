
#include "FileSystemDataStructure.h"
#include "ErrorHandling.h"
#include "TreeNode.h"

/** FileSystemNode Constructors **/

FileSystemNode::FileSystemNode(const std::string &name, bool isFile) {
    this->name = name;
    this->file = isFile;
}

FileSystemNode::FileSystemNode(std::string &name, FileSystemNode *parent, bool isFile) {
    this->name = name;
    this->file = isFile;
    this->parent = parent;
}

/** FileSystemNode Constant Methods **/

bool FileSystemNode::isFile() const { return file; }

FileSystemNode *FileSystemNode::getParent() const {
    return parent;
}

std::vector<FileSystemNode *> FileSystemNode::getChildren() const {
    return children;
}

std::string FileSystemNode::getName() {
    return name;
}


/** FileSystemNode Non-Constant Methods **/

void FileSystemNode::addChild(FileSystemNode *child) {
    children.push_back(child);
}

bool FileSystemNode::removeChild(FileSystemNode *child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        const auto element = *it;

        // child to be removed found
        if (element == child) {
            children.erase(it);
            return true;
        }
    }

    // node to be removed isn't a child of this node
    return false;
}

void FileSystemNode::setParent(FileSystemNode *node) {
    parent = node;
}

void FileSystemNode::rename(const std::string &newName) {
    if (newName.empty()) {
        ErrorHandling::handleError(ErrorCode::InvalidName);
        return;
    }
    name = newName;
}


/** FileSystemDataStructure Constructors **/


// singleton instance
FileSystemDataStructure *FileSystemDataStructure::instance = nullptr;

FileSystemDataStructure *FileSystemDataStructure::getInstance() {
    // if no instance was created, create an instance and return it
    // else return the existing instance
    if (!instance)
        instance = new FileSystemDataStructure();

    return instance;
}


FileSystemDataStructure::FileSystemDataStructure() {
    root = new FileSystemNode("Root", false);
    currentDir = root;
}

/** Methods **/
FileSystemNode* FileSystemDataStructure::getCurrentDir() const {
    return currentDir;
}
FileSystemNode* FileSystemDataStructure::getRoot() const {
    return root;
}
void FileSystemDataStructure::setRoot(FileSystemNode* newRoot){
    root = newRoot;
}
void FileSystemDataStructure::setCurrentDir(FileSystemNode* dir){
    currentDir = dir;
}
