
#ifndef VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
#define VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H

#include <string>
#include <vector>
#include <iostream>

#include <TreeNode.h>


/** class FileSystemNode representing a File system Tree Node **/
class FileSystemNode{

public:
    /* constructors  */
    FileSystemNode(const std::string &name, bool isFile);
    FileSystemNode(std::string& name, FileSystemNode* Parent, bool file);

    /* constant methods */
    bool isFile() const;
    FileSystemNode* getParent() const;
    std::vector<FileSystemNode*> getChildren() const;
    std::string getName();

    /* non-constant methods */

    /**
     * Add a child node
     *
     * @param child Pointer to child node to be added
     * */
    void addChild(FileSystemNode* child);
    /**
     * Remove a child node from the current node.
     *
     * @param child Pointer to the child node to be removed.
     * @return True if the child node was found and removed successfully, False otherwise.
     */
    bool removeChild(FileSystemNode *child);
    /**
     * Set the parent of the Current FileSystemNode
     * @param node Pointer to the parent node
     * */
    void setParent(FileSystemNode* node);
    /**
     * sets name to newName
     * */
    void rename(const std::string &newName);

private:
    std::string name;
    std::vector<FileSystemNode*> children;
    FileSystemNode* parent = nullptr;
    bool file;

};

/*
 * The FileSystemDataStructure class follows the singleton design pattern to provide a centralized and globally accessible
 * instance of the file system's directory structure. This ensures consistency and simplifies access to the file system across
 * different components of the application.
 * */
class FileSystemDataStructure{
public:
    /** singleton getInstance() */
    static FileSystemDataStructure* getInstance();

    /** public methods **/
    FileSystemNode* getCurrentDir() const;
    FileSystemNode* getRoot() const;
    void setRoot(FileSystemNode*);
    void setCurrentDir(FileSystemNode*);

private:

    /** Singleton private constructor & instance **/
    FileSystemDataStructure();
    static FileSystemDataStructure* instance;

    /** Private Data Members **/
    FileSystemNode* root = nullptr;           // The root node of the file system data structure
    FileSystemNode* currentDir = nullptr;     // The current directory node
};



#endif //VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
