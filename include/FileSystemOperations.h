
#ifndef VIRTUAL_FILE_SYSTEM_FILESYSTEMOPERATIONS_H
#define VIRTUAL_FILE_SYSTEM_FILESYSTEMOPERATIONS_H

#include <string>
#include <vector>

#include "TreeNode.h"
#include "FileSystemDataStructure.h"


class FileSystemOperations{
public:

    /** Constant Methods */

    /**
    * @brief get directories inside current directory
    * @returns a vector of strings (Directories Names), returns an empty vector if current directory is null
    * */
    static std::vector<std::string> getDirectoriesNames();
    /**
     * @brief get files inside current directory
     * @returns a vector of String (Files Names), returns an empty vector if current directory is null
     * */
    static std::vector<std::string> getFilesNames();

    /**
     * @brief presents the currentDirectory file Hierarchy in a tree data structure form
     * driver for the recursive function getTreePresentation
     * @return TreeNode pointer to the root
     * */
    static TreeNode *getTreePresentation();
    static std::string getCurrentPath();

    /** Non-Constant Methods */

    /**
     * @brief Add a directory to the current Directory.
     * @param directoryName The name of the directory to be added.
     */
    static void createDirectory(const std::string & directoryName);
    /**
     * @brief Add a file to the current Directory.
     * @param fileName The name of the file to be added.
     */
    static void createFile(const std::string& fileName);
    /**
     * @brief changes the current directory
     * @param path string relative path of the destination directory
     *
     * */
    static void changeDirectory(const std::string &path);
    /**
     * @brief removes a directory that is a direct child of the current dir
     * if directory doesn't exist or directory isn't empty, an error is reported to ErrorHandling Component
     * @param directoryName name of directory to be deleted
     * */
    static void removeDirectory(const std::string &directoryName);
    /**
     * @brief removes a child-file of current one
     * if file doesn't exist, an error is reported to ErrorHandling Component
     * @param fileName name of file to be deleted
     * */
    static void removeFile(const std::string &fileName);
    /**
     * renames a child-file of current directory
     * if file doesn't exist or new filename is empty, an error is reported to ErrorHandling Component
     * @param initialFileName initial name of file to be renamed
     * @param newFileName new name the file will be renamed to
     * */
    static void renameFile(const std::string &initialFileName, const std::string &newFileName);        /**
     * renames a child-directory of current directory
     * if directory doesn't exist or new directory name is empty, an error is reported to ErrorHandling Component
     * @param initialDirName initial name of dir to be renamed
     * @param newDirName new name the dir will be renamed to
     * */
    static void renameDir(const std::string &initialDirName,const std::string &newDirName);

private:

    /** FileSystemDataStructure instance  **/
    static FileSystemDataStructure* fileSystem;

    /** Private Methods **/

    /**
     * Helper method to find a directory with the given name in the current directory.
     * @returns a pointer to the directory if found. Returns nullptr if directory not found
     * */
    static FileSystemNode* findDirectory(const std::string& directoryName);
    /**
     * Helper method to find a file with the given name in the current directory.
     * returns a pointer to the file if found. Returns nullptr if file not found
     * */
    static FileSystemNode* findFile(const std::string& fileName);
    /**
     * recursive function to represent directory hierarchy in form of a tree data strucutre
     * @param node FileSystemDataStructure used FileSystemNode (should have a getName method and a getChildren method)
     * @return TreeNode pointer, nullptr if node is nullptr
     * */
    static TreeNode *getTreePresentation(FileSystemNode *node);
    /**
     * @brief moves to a directory
     * if directory doesn't exist, report error to ErrorHandling Component
     * @param dirName String represents the name of directory to move to
     * @note dirName ".." references the parent of current directory
     * */
    static void goToDir(const std::string& dirName);

    /**
   * get directories inside current directory
   * @returns a vector of FileSystemNode* (Directories), returns an empty vector if current directory is null
   * */
    static std::vector<FileSystemNode*> getDirectories();
    /**
     * get files inside current directory
     * @returns a vector of FileSystemNode* (Files), returns an empty vector if current directory is null
     * */
    static std::vector<FileSystemNode*> getFiles();

    /**
     * @breif checks if a file name is valid
     * */
    static bool isValidFileName(const std::string&) ;
    /**
     * @breif checks if a directory name is valid
     * */
    static bool isValidDirName(const std::string&) ;
};


#endif //VIRTUAL_FILE_SYSTEM_FILESYSTEMOPERATIONS_H
