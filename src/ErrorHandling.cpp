#include "ErrorHandling.h"

#include <iostream>

std::unordered_map<ErrorCode, std::string> ErrorHandling::errorMessages;

void ErrorHandling::initialize() {
    // Initialize the error messages
    errorMessages[ErrorCode::InvalidFileName] = "The file name contains invalid characters(/, \\ or spaces).";
    errorMessages[ErrorCode::InvalidDirName] = "The file name contains invalid characters(/, \\, or spaces).";
    errorMessages[ErrorCode::InvalidDirName] = "The file/directory name contains invalid characters(/, \\, or spaces).";
    errorMessages[ErrorCode::FileDoesntExist] = "No File with this name in this directory";
    errorMessages[ErrorCode::DirDoesntExist] = "No directory with this name in current directory.";
    errorMessages[ErrorCode::FileAlreadyExists] = "There is a file in this directory with this name already.";
    errorMessages[ErrorCode::DirAlreadyExists] = "There is a directory in this directory with this name already.";
    errorMessages[ErrorCode::DirNotEmpty] = "Can't Delete a non-empty directory.";
}

void ErrorHandling::handleError(ErrorCode errorCode) {
    std::string errorMessage = errorMessages[errorCode];
    std::cout << "Error: " << errorMessage << std::endl;
}