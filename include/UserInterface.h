#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "FileSystemDataStructure.h"
#include "FileSystemOperations.h"

/**
 * @brief The UserInterface class handles user interactions and commands.
 *
 * It provides a command line interface for users to interact with the file system.
 */
class UserInterface {
public:

    UserInterface();

    /**
     * @brief Runs the user interface, accepting user commands and processing them.
     */
    void run();


private:
    /**
     * Map of command names to the number of expected arguments.
     */
    std::map<std::string,int> argumentsNumber;

    /**
     * @brief Parses the user command into command type and arguments.
     * @param command The user command string.
     * @param commandType Output parameter for the command type.
     * @param arguments Output parameter for the command arguments.
     */
    static void parseCommand(const std::string& inputCommand, std::string& commandType, std::vector<std::string>& arguments);

    /**
     * @brief Processes the user command.
     * @param command The user command string.
     */
    void processCommand(const std::string& command);

    /**
     * @brief Validates the user command and its arguments.
     * @param commandType The command type.
     * @param args The command arguments.
     * @return True if the command is valid, false otherwise.
     */
    bool validateCommand(const std::string& commandType, std::vector<std::string>& args);

    // Command handlers
    static void handleChangeDir(const std::vector<std::string>& args);
    static void handleCreateDir(const std::vector<std::string>& args);
    static void handleCreateFile(const std::vector<std::string>& args);
    static void handleRemoveDir(const std::vector<std::string>& args);
    static void handleRemoveFile(const std::vector<std::string>& args);
    static void handleRenameFile(const std::vector<std::string>& args);
    static void handleRenameDir(const std::vector<std::string>& args);
    static void handleList(const std::vector<std::string>& args);
    static void handleHierarchyList(const std::vector<std::string>& args);
    static void handleHelp(const std::vector<std::string>& args);

    /* Helper method to print a tree recursively*/
    static void printTree(TreeNode* root, int depth);

};

#endif // USERINTERFACE_H
