
#ifndef VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
#define VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H

#include <string>
#include <vector>
#include <iostream>

#include <TreeNode.h>

class FileSystemDataStructure{
private:
    /** private class Node representing a File system Tree Node **/
    class Node{
    public:
        /* constructors  */
        Node(const std::string &name, bool file);
        Node(std::string& name, Node* Parent, bool file);

        /* constant methods */
        bool isFile() const;
        Node* getParent() const;
        std::vector<Node*> getChildren() const;
        std::string getName();

        /* non-constant methods */

        /**
         * Add a child node
         *
         * @param child Pointer to child node to be added
         * */
        void addChild(Node* child);
        /**
         * Remove a child node from the current node.
         *
         * @param child Pointer to the child node to be removed.
         * @return True if the child node was found and removed successfully, False otherwise.
         */
        bool removeChild(FileSystemDataStructure::Node *child);
        /**
         * Set the parent of the Current Node
         * @param node Pointer to the parent node
         * */
        void setParent(Node* node);
        /**
         * sets name to newName
         * */
        void rename(std::string& newName);

    private:
        std::string name;
        std::vector<Node*> children;
        Node* parent = nullptr;
        bool file;

    };

public:

    /** Constructors */

    FileSystemDataStructure();

    /** Constant Methods */

    /**
   * get directories inside current directory
   * @returns a vector of Node* (Directories), returns an empty vector if current directory is null
   * */
    std::vector<Node*> getDirectories() const;
    /**
     * get files inside current directory
     * @returns a vector of Node* (Files), returns an empty vector if current directory is null
     * */
    std::vector<Node*> getFiles() const;

    /**
     * presents the currentDirectory file Hierarchy in a tree data structure form
     * driver for the recursive function getTreePresentation
     * @return TreeNode pointer to the root
     * */
    TreeNode *getTreePresentation() const ;


    /** Non-Constant Methods */

    /**
     * Add a directory to the current Directory.
     * @param directoryName The name of the directory to be added.
     */
    void createDirectory(const std::string & directoryName);
    /**
     * Add a file to the current Directory.
     * @param fileName The name of the file to be added.
     */
    void createFile(const std::string& fileName);
    /**
     * changes current directory
     * if directory doesn't exist, report error to ErrorHandling Component
     * @param directoryName String represents the name of directory to move to
     * */
    void changeDirectory(std::string& directoryName);
    /**
     * removes a child-directory of current one
     * if directory doesn't exist or directory isn't empty, an error is reported to ErrorHandling Component
     * @param directoryName name of directory to be deleted
     * */
    void removeDirectory(std::string& directoryName);
    /**
     * removes a child-file of current one
     * if file doesn't exist, an error is reported to ErrorHandling Component
     * @param fileName name of file to be deleted
     * */
    void removeFile(std::string& fileName);
    /**
     * renames a child-file of current directory
     * if file doesn't exist or new filename is empty, an error is reported to ErrorHandling Component
     * @param initialFileName initial name of file to be renamed
     * @param newFileName new name the file will be renamed to
     * */
    void renameFile(std::string& initialFileName, std::string& newFileName);
private:

    /** Private Data Members **/
    Node* root = nullptr;           // The root node of the file system data structure
    Node* currentDir = nullptr;     // The current directory node

    /** Private Methods **/

    /**
     * Helper method to find a directory with the given name in the current directory.
     * @returns a pointer to the directory if found. Returns nullptr if directory not found
     * */
    Node* findDirectory(const std::string& directoryName) const;

    /**
     * Helper method to find a file with the given name in the current directory.
     * returns a pointer to the file if found. Returns nullptr if file not found
     * */
    Node* findFile(const std::string& fileName) const;
    /**
     * recursive function to represent directory hierarchy in form of a tree data strucutre
     * @param node FileSystemDataStructure used Node (should have a getName method and a getChildren method)
     * @return TreeNode pointer, nullptr if node is nullptr
     * */
    TreeNode *getTreePresentation(Node *node) const;


};

#endif //VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
