
#ifndef VIRTUAL_FILE_SYSTEM_ERRORHANDLING_H
#define VIRTUAL_FILE_SYSTEM_ERRORHANDLING_H

#include <string>
#include <unordered_map>

enum class ErrorCode {
    InvalidFileName,
    InvalidDirName,
    FileDoesntExist,
    DirDoesntExist,
    FileAlreadyExists,
    DirAlreadyExists

};

class ErrorHandling {
public:
    static void initialize(); // Initialize the error messages

    static void handleError(ErrorCode errorCode); // Handle and report the error

private:
    static std::unordered_map<ErrorCode, std::string> errorMessages;
};
#endif //VIRTUAL_FILE_SYSTEM_ERRORHANDLING_H
