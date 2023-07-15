
#include "FileSystemDataStructure.h"
#include "ErrorHandling.h"
#include "TreeNode.h"

/** FileSystemDataStructure::Node Constructors **/

FileSystemDataStructure::Node::Node(const std::string &name, bool file) {
    this->name = name;
    this->file = file;
}

FileSystemDataStructure::Node::Node(std::string &name, FileSystemDataStructure::Node *Parent, bool isFile) {
    this->name = name;
    this->file = isFile;
}

/** FileSystemDataStructure::Node Constant Methods **/

bool FileSystemDataStructure::Node::isFile() const { return file; }

FileSystemDataStructure::Node* FileSystemDataStructure::Node::getParent() const
{
    return parent;
}

std::vector<FileSystemDataStructure::Node *> FileSystemDataStructure::Node::getChildren() const {
    return children;
}

std::string FileSystemDataStructure::Node::getName() {
    return name;
}


/** FileSystemDataStructure::Node Non-Constant Methods **/

void FileSystemDataStructure::Node::addChild(FileSystemDataStructure::Node *child) {
    children.push_back(child);
}

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

void FileSystemDataStructure::Node::setParent(FileSystemDataStructure::Node *node) {
    parent = node;
}

void FileSystemDataStructure::Node::rename(std::string &newName) {
    if(newName.empty()) {
        ErrorHandling::handleError(ErrorCode::InvalidName);
        return;
    }
    name = newName;
}


/** FileSystemDataStructure Constructors **/

FileSystemDataStructure::FileSystemDataStructure() {
    root = new Node("Root",false);
    currentDir = root;
}


/** FileSystemDataStructure Non-Constant Methods **/


void FileSystemDataStructure::createDirectory(const std::string &directoryName) {

    // check if the name is an empty string (which is invalid)
    if(directoryName.empty()) {
        ErrorHandling::handleError(ErrorCode::InvalidDirName);
        return;
    }

    // check if already exists a directory with this name
    if(findDirectory(directoryName)){
        ErrorHandling::handleError(ErrorCode::DirAlreadyExists);
        return;
    }

    auto dir = new Node(directoryName,false);

    // if the Data Structure is empty, add the directory as the root
    // otherwise, add it as a child to the current dir
    if(currentDir){
        dir->setParent(currentDir);
        currentDir->addChild(dir);
    }
    else {
        currentDir = dir;
        root = dir;
    }
}

void FileSystemDataStructure::createFile(const std::string &fileName)  {
    // check if the name is an empty string (which is invalid)
    if(fileName.empty()){
        ErrorHandling::handleError(ErrorCode::InvalidFileName);
    }

    // check if already exists a file with this name
    if(findFile(fileName)){
        ErrorHandling::handleError(ErrorCode::FileAlreadyExists);
        return;
    }

    auto file = new Node(fileName,true);

    // if the Data Structure is empty, report an Invalid State Error
    // otherwise, add it as a child to the current dir
    if(currentDir){
        file->setParent(currentDir);
        currentDir->addChild(file);
    }
    else {
        ErrorHandling::handleError(ErrorCode::InvalidState);
    }
}

void FileSystemDataStructure::changeDirectory(std::string &directoryName) {
    auto dir = findDirectory(directoryName);

    if(dir) {
        currentDir = dir;

    }else{
        ErrorHandling::handleError(ErrorCode::DirDoesntExist);
    }
}

void FileSystemDataStructure::removeDirectory(std::string &directoryName) {
    auto dir = findDirectory(directoryName);

    // guard checks if directory doesn't exist
    if (!dir) {
        ErrorHandling::handleError(ErrorCode::DirDoesntExist);
        return;
    }

    // guard checks if directory isn't empty
    bool isEmptyDirectory = dir->getChildren().empty();
    if (!isEmptyDirectory) {
        ErrorHandling::handleError(ErrorCode::DirNotEmpty);
        return;
    }

    currentDir->removeChild(dir);
}

void FileSystemDataStructure::removeFile(std::string &fileName) {
    auto dir = findDirectory(fileName);

    // guard checks if file doesn't exist
    if (!dir) {
        ErrorHandling::handleError(ErrorCode::FileDoesntExist);
        return;
    }

    currentDir->removeChild(dir);
}

void FileSystemDataStructure::renameFile(std::string& initialFileName, std::string& newFileName){

    // guard makes sure the new filename isn't empty
    if(newFileName.empty())
    {
        ErrorHandling::handleError(ErrorCode::InvalidFileName);
        return;
    }

    auto file = findFile(initialFileName);
    if(file){
        file->rename(newFileName);
    }
    // if file doesn't exist
    else{
        ErrorHandling::handleError(ErrorCode::FileDoesntExist);
    }

}


/** FileSystemDataStructure Private Methods **/

std::vector<FileSystemDataStructure::Node *> FileSystemDataStructure::getDirectories() const {
    std::vector<FileSystemDataStructure::Node *> directories;

    if(currentDir) {
        for (auto dir:currentDir->getChildren()) {
            if(!dir->isFile())
                directories.push_back(dir);
        }
    }

    return directories;
}


std::vector<FileSystemDataStructure::Node *> FileSystemDataStructure::getFiles() const {
    std::vector<FileSystemDataStructure::Node *> files;

    if(currentDir) {
        for (auto file:currentDir->getChildren()) {
            if(file->isFile())
                files.push_back(file);
        }
    }

    return files;
}

FileSystemDataStructure::Node* FileSystemDataStructure::findDirectory(const std::string &directoryName) const {
    auto directories = getDirectories();

    for (auto dir:directories) {
        if(dir->getName() == directoryName) return dir;
    }

    return nullptr;
}

FileSystemDataStructure::Node *FileSystemDataStructure::findFile(const std::string &fileName) const {
    auto files = getFiles();

    for (auto file:files) {
        if(file->getName() == fileName) return file;
    }

    return nullptr;
}

TreeNode *FileSystemDataStructure::getTreePresentation(FileSystemDataStructure::Node *node) const {
    // guard makesSure that node isn't nullptr
    if(!node) return nullptr;

    auto treeNode = new TreeNode(node->getName());
    for (auto child: node->getChildren()) {
        auto treeNodeChild = getTreePresentation(child);
        if(treeNodeChild)
            treeNode->addChild(treeNodeChild);
    }

    return treeNode;
}
TreeNode *FileSystemDataStructure::getTreePresentation() const {
    return getTreePresentation(currentDir);
}

FileSystemDataStructure *FileSystemDataStructure::getInstance() {
    // if no instance was created, create an instance and return it
    // else return the existing instance
    if(!instance)
        instance = new FileSystemDataStructure();

    return instance;
}



