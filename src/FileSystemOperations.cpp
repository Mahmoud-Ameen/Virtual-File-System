
#include "FileSystemOperations.h"
#include "FileSystemDataStructure.h"
#include "ErrorHandling.h"

/** initialize static member fileSystem with an instance of FileSystemDataStructure **/
FileSystemDataStructure* FileSystemOperations::fileSystem =  FileSystemDataStructure::getInstance();

/** FileSystemDataStructure Non-Constant Methods **/


void FileSystemOperations::createDirectory(const std::string &directoryName) {

    // check if dir name is invalid
    if (!isValidDirName(directoryName)) {
        ErrorHandling::handleError(ErrorCode::InvalidDirName);
        return;
    }

    // check if already exists a directory with this name
    if (findDirectory(directoryName)) {
        ErrorHandling::handleError(ErrorCode::DirAlreadyExists);
        return;
    }

    auto dir = new FileSystemNode(directoryName, false);

    // if the Data Structure is empty, add the directory as the root
    // otherwise, add it as a child to the current dir
    auto currentDir = fileSystem->getCurrentDir();
    if (currentDir) {
        dir->setParent(currentDir);
        currentDir->addChild(dir);
    } else {
        fileSystem->setCurrentDir(dir);
        fileSystem->setRoot(dir);
    }
}

bool FileSystemOperations::isValidFileName(const std::string &fileName) {
    // gets the index of the '.' char which is the start of the file extension
    auto dotIndex = fileName.find('.');

    // there is no "."
    if (dotIndex == std::string::npos) return false;

    // file has no name (other than the extension)
    std::string plainName = fileName.substr(0, dotIndex);
    if (plainName.empty()) return false;

    // extension is empty
    std::string extension = fileName.substr(dotIndex + 1, std::string::npos);
    if (extension.empty()) return false;

    //otherwise
    return true;

}

bool FileSystemOperations::isValidDirName(const std::string &dirName) {
    bool containsSlash = dirName.find('/') != std::string::npos;
    bool containsBackSlash = dirName.find('\\') != std::string::npos;
    bool containsSpace = dirName.find(' ') != std::string::npos;
    bool isEmpty = dirName.empty();

    return !(containsSlash || containsBackSlash || containsSpace || isEmpty);
}

void FileSystemOperations::createFile(const std::string &fileName) {

    if (!isValidFileName(fileName)) {
        ErrorHandling::handleError(ErrorCode::InvalidFileName);
        return;
    }

    // check if already exists a file with this name
    if (findFile(fileName)) {
        ErrorHandling::handleError(ErrorCode::FileAlreadyExists);
        return;
    }

    auto file = new FileSystemNode(fileName, true);

    // if the Data Structure is empty, report an Invalid State Error
    // otherwise, add it as a child to the current dir
    auto currentDir = fileSystem->getCurrentDir();
    if (currentDir) {
        file->setParent(currentDir);
        currentDir->addChild(file);
    } else {
        ErrorHandling::handleError(ErrorCode::InvalidState);
    }
}

void FileSystemOperations::changeDirectory(const std::string &path) {

    std::vector<std::string> dirs;
    std::string tempDirName;
    for (char ch: path) {
        if (ch == '/' || ch == '\\') {
            dirs.push_back(tempDirName);
            tempDirName = "";
            continue;
        }

        tempDirName.push_back(ch);
    }
    if(!tempDirName.empty()) dirs.push_back(tempDirName);

    for (auto& dirName : dirs){
        goToDir(dirName);
    }
}

void FileSystemOperations::removeDirectory(const std::string &directoryName) {
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

    auto currentDir = fileSystem->getCurrentDir();
    currentDir->removeChild(dir);
}

void FileSystemOperations::removeFile(const std::string &fileName) {
    auto file = findFile(fileName);

    // guard checks if file doesn't exist
    if (!file) {
        ErrorHandling::handleError(ErrorCode::FileDoesntExist);
        return;
    }

    auto currentDir = fileSystem->getCurrentDir();
    currentDir->removeChild(file);
}

void FileSystemOperations::renameFile(const std::string &initialFileName, const std::string &newFileName) {

    // guard makes sure the new filename is Valid
    if (!isValidFileName(newFileName)) {
        ErrorHandling::handleError(ErrorCode::InvalidFileName);
        return;
    }

    auto file = findFile(initialFileName);
    if (file) {
        file->rename(newFileName);
    }
        // if file doesn't exist
    else {
        ErrorHandling::handleError(ErrorCode::FileDoesntExist);
    }

}

void FileSystemOperations::renameDir(const std::string &initialDirName,const std::string &newDirName) {

    // guard makes sure the new newDirName is valid
    if (!isValidDirName(newDirName)) {
        ErrorHandling::handleError(ErrorCode::InvalidFileName);
        return;
    }

    auto dir = findDirectory(initialDirName);
    if (dir) {
        dir->rename(newDirName);
    }
        // if dir doesn't exist
    else {
        ErrorHandling::handleError(ErrorCode::FileDoesntExist);
    }
}

/** FileSystemDataStructure Constant Methods **/

std::vector<FileSystemNode *> FileSystemOperations::getDirectories() {
    std::vector<FileSystemNode *> directories;
    auto currentDir = fileSystem->getCurrentDir();

    if (currentDir) {
        for (auto dir: currentDir->getChildren()) {
            if (!dir->isFile())
                directories.push_back(dir);
        }
    }

    return directories;
}

std::vector<FileSystemNode *> FileSystemOperations::getFiles() {
    std::vector<FileSystemNode *> files;
    auto currentDir = fileSystem->getCurrentDir();

    if (currentDir) {
        for (auto file: currentDir->getChildren()) {
            if (file->isFile())
                files.push_back(file);
        }
    }

    return files;
}

std::string FileSystemOperations::getCurrentPath() {
    std::string path;
    auto currentDir = fileSystem->getCurrentDir();

    auto dir = currentDir;
    while (dir) {
        path = dir->getName() + "/" + path;
        dir = dir->getParent();
    }
    return path;
}

std::vector<std::string> FileSystemOperations::getDirectoriesNames() {
    auto dirs = getDirectories();
    std::vector<std::string> dirsNames;

    dirsNames.reserve(dirs.size());
    for (auto dir: dirs) {
        dirsNames.push_back(dir->getName());
    }

    return dirsNames;
}

std::vector<std::string> FileSystemOperations::getFilesNames() {
    auto files = getFiles();
    std::vector<std::string> filesNames;

    filesNames.reserve(files.size());
    for (auto dir: files) {
        filesNames.push_back(dir->getName());
    }

    return filesNames;
}

TreeNode *FileSystemOperations::getTreePresentation() {
    auto currentDir = fileSystem->getCurrentDir();

    return getTreePresentation(currentDir);
}


/** FileSystemDataStructure Private Methods **/

void FileSystemOperations::goToDir(const std::string& dirName){
    auto currentDir = fileSystem->getCurrentDir();

    // go back
    if (dirName == "..") {
        if (currentDir->getParent())
            fileSystem->setCurrentDir(currentDir->getParent());
        return;
    }

    auto dir = findDirectory(dirName);
    if (dir)
        fileSystem->setCurrentDir(dir);
    else
        ErrorHandling::handleError(ErrorCode::DirDoesntExist);

};


FileSystemNode *FileSystemOperations::findDirectory(const std::string &directoryName) {
    auto directories = getDirectories();

    for (auto dir: directories) {
        if (dir->getName() == directoryName) return dir;
    }

    return nullptr;
}

FileSystemNode *FileSystemOperations::findFile(const std::string &fileName) {
    auto files = getFiles();

    for (auto file: files) {
        if (file->getName() == fileName) return file;
    }

    return nullptr;
}

TreeNode *FileSystemOperations::getTreePresentation(FileSystemNode *node) {
    // guard makesSure that node isn't nullptr
    if (!node) return nullptr;

    auto treeNode = new TreeNode(node->getName());
    for (auto child: node->getChildren()) {
        auto treeNodeChild = getTreePresentation(child);
        if (treeNodeChild)
            treeNode->addChild(treeNodeChild);
    }

    return treeNode;
}
