

#ifndef VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
#define VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H

#include <string>
#include <vector>

class FileSystemDataStructure{

public:

private:
    class Node{
    public:
        /* constructors  */
        explicit Node(std::string& name, bool file);
        Node(std::string& name, Node* Parent, bool file);

        /* constant methods */
        bool isFile() const;
        Node* getParent() const;
        std::vector<Node*> getChildren() const;

        /* non-constant methods */
        void addChild(Node* child);
        bool removeChild(FileSystemDataStructure::Node *child);
        void setParent(Node* node);

    private:
        std::string name;
        std::vector<Node*> children;
        Node* parent = nullptr;
        bool file;

    };

};

#endif //VIRTUAL_FILE_SYSTEM_FILESYSTEMDATASTRUCTURE_H
