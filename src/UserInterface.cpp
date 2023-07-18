#include <algorithm>

#include "UserInterface.h"
#include "ErrorHandling.h"
#include "FileSystemOperations.h"

UserInterface::UserInterface(){

    argumentsNumber["help"] = 0;
    argumentsNumber["ls"] = 0;
    argumentsNumber["lsh"] = 0;
    argumentsNumber["cd"] = 1;
    argumentsNumber["mkdir"] = 1;
    argumentsNumber["touch"] = 1;
    argumentsNumber["rm"] = 1;
    argumentsNumber["rmdir"] = 1;
    argumentsNumber["rename"] = 2;
    argumentsNumber["renameDir"] = 2;
}

/** Public methods */
void UserInterface::run() {

    while (true) {
        // Read user input
        std::string command;

        std::cout <<FileSystemOperations::getCurrentPath() << "> ";
        std::getline(std::cin, command);

        // Check for exit command
        if (command == "exit") {
            break;
        }

        processCommand(command);
    }
}

/** Private Methods **/

bool UserInterface::validateCommand(const std::string& commandType,std::vector<std::string>& args){
    if(UserInterface::argumentsNumber.find(commandType) == UserInterface::argumentsNumber.end())
        return true;

    return (UserInterface::argumentsNumber[commandType] == args.size());
}

void UserInterface::processCommand(const std::string &inputCommand){
    // parse the command
    std::string commandType;
    std::vector<std::string> args;
    parseCommand(inputCommand,commandType,args);

    if(!validateCommand(commandType,args)){
        std::cout <<"Number of arguments doesn't match command\n";
        return;
    }

    if(commandType == "cd")
        handleChangeDir(args);

    else if(commandType == "mkdir")
        handleCreateDir(args);

    else if (commandType =="touch")
        handleCreateFile(args);

    else if (commandType == "ls")
        handleList(args);

    else if (commandType == "rmdir")
        handleRemoveDir(args);

    else if (commandType == "rm")
        handleRemoveFile(args);

    else if (commandType == "rename")
        handleRenameFile(args);

    else if (commandType == "renameDir")
        handleRenameDir(args);

    else if (commandType == "lsh")
        handleHierarchyList(args);

    else if (commandType == "help")
        handleHelp(args);

    else
        std::cout << "Unknown Command. For details about supported commands type 'help'\n";
}

std::string trimString(const std::string& str) {
    std::string trimmedStr = str;
    // Trim spaces from the left side
    trimmedStr.erase(trimmedStr.begin(), std::find_if(trimmedStr.begin(), trimmedStr.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Trim spaces from the right side
    trimmedStr.erase(std::find_if(trimmedStr.rbegin(), trimmedStr.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), trimmedStr.end());

    return trimmedStr;
}

void UserInterface::parseCommand(const std::string &inputCommand, std::string &commandType,
                                 std::vector<std::string> &arguments) {

    std::string command = trimString(inputCommand);

    // get command type
    commandType = "";
    int lastProcessedIndex = -1;
    for (int i = 0; i < command.size(); i++) {
        lastProcessedIndex = i;
        char ch = command[i];

        if(ch == ' ' && !commandType.empty()) {
            break;
        }
        commandType.push_back(ch);
    }

    // checks if the command is fully processed
    if(lastProcessedIndex + 1 >= command.size()) return;

    arguments.clear();
    std::string argument;
    for (int i = lastProcessedIndex + 1; i < command.size(); ++i) {
        if(command[i] == ' '){
            if(!argument.empty()) {
                arguments.push_back(argument);
                argument = "";
            }
            continue;
        }

        argument.push_back(command[i]);
    }
    if(!argument.empty()) arguments.push_back(argument);

}

void UserInterface::handleChangeDir(const std::vector<std::string> &args) {
    FileSystemOperations::changeDirectory(args[0]);
}
void UserInterface::handleCreateDir(const std::vector<std::string> &args) {
    FileSystemOperations::createDirectory(args[0]);
}
void UserInterface::handleCreateFile(const std::vector<std::string> &args) {
    FileSystemOperations::createFile(args[0]);
}
void UserInterface::handleList(const std::vector<std::string> &args) {
    auto dirs = FileSystemOperations::getDirectoriesNames();
    auto files = FileSystemOperations::getFilesNames();

    std::string space = "     ";
    for (const auto & dir : dirs) {
        std::cout << "*" << dir << '\n';
    }
    for (const auto & file : files) {
        std::cout << file << '\n';
    }
}
void UserInterface::handleRemoveDir(const std::vector<std::string> &args) {
    FileSystemOperations::removeDirectory(args[0]);
}
void UserInterface::handleRemoveFile(const std::vector<std::string> &args) {
    FileSystemOperations::removeFile(args[0]);
}
void UserInterface::handleRenameFile(const std::vector<std::string> &args){
    FileSystemOperations::renameFile(args[0],args[1]);
}
void UserInterface::handleRenameDir(const std::vector<std::string> &args){
    FileSystemOperations::renameDir(args[0],args[1]);
}
void UserInterface::handleHierarchyList(const std::vector<std::string> &args) {
    auto tree = FileSystemOperations::getTreePresentation();
    printTree(tree,0);
}

void UserInterface::printTree(TreeNode* root, int depth){
    for (int i = 0; i < depth; ++i) {
        std::cout<<"--";
    }
    std::cout<<"\\" + root->name << std::endl;
    for (auto child:root->children) {
        printTree(child,depth+1);
    }
}

void UserInterface::handleHelp(const std::vector<std::string> &args) {
    std::cout <<"Supported Commands List:\n"
                "1- mkdir [directoryName]\n"
                "creates a directory named [directoryName].\n"
                "directoryName must not contain /, \\ or spaces\n"
                "\n"

                "2- rmdir [directoryName]\n"
                "removes the directory named [directoryName] in current directory\n"
                "\n"

                "3- cd [path]\n"
                "changes current directory to the specified path.\n"
                "path '..' refers to the parent of current directory.\n"
                "example of an accepted path '../mahmoud/desktop'\n"
                "\n"

                "4- touch [fileName]\n"
                "creates a file named [fileName]\n"
                "fileName must follow the form '[name].[extension]'\n"
                "fileName must not contain any /, \\ or spaces\n"
                "\n"

                "5- rm [fileName]\n"
                "removes the file named [fileName] in current directory\n"
                "\n"

                "6- rename [initialFileName] [newFileName]\n"
                "rename the file named [initialFileName] in current directory to [newFileName].\n"
                "\n"

                "7- renameDir [initialDirName] [newDirName]\n"
                "rename the Dir named [initialDirName] in current directory to [newDirName].\n"
                "\n"

                "8- ls\n"
                "lists all directories and files in current directory.\n"
                "directories are prefixed with an asterisk.\n"
                "\n"

                "9- lsh\n"
                "shows the folders hierarchy.\n"
                "lists all directories and files in current directory and for each directory, its content is listed too.\n"
                "\n"

                "10- help\n"
                "shows this info message.\n";
}