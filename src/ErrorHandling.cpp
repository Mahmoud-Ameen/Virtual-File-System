#include "ErrorHandling.h"

#include <iostream>

std::unordered_map<ErrorCode, std::string> ErrorHandling::errorMessages;

void ErrorHandling::initialize() {
    // Initialize the error messages
    errorMessages[ErrorCode::InvalidFileName] = "Invalid File Name.";
    errorMessages[ErrorCode::InvalidDirName] = "Invalid Directory Name.";
    errorMessages[ErrorCode::FileDoesntExist] = "No File with this name in this directory";
    errorMessages[ErrorCode::FileAlreadyExists] = "There is a file in this directory with this name already.";
    errorMessages[ErrorCode::DirAlreadyExists] = "There is a directory in this directory with this name already.";
    errorMessages[ErrorCode::DirNotEmpty] = "Can't Delete a non-empty directory.";
}

void ErrorHandling::handleError(ErrorCode errorCode) {
    std::string errorMessage = errorMessages[errorCode];
    std::cout << "Error: " << errorMessage << std::endl;
}