#include "ErrorHandling.h"

#include <iostream>

std::unordered_map<ErrorCode, std::string> ErrorHandling::errorMessages;

void ErrorHandling::initialize() {
    // Initialize the error messages
    errorMessages[ErrorCode::InvalidFileName] = "Invalid File Name.";
    errorMessages[ErrorCode::InvalidDirName] = "Invalid Directory Name.";
    errorMessages[ErrorCode::FileDoesntExist] = "No File with this name in this directory";
}

void ErrorHandling::handleError(ErrorCode errorCode) {
    std::string errorMessage = errorMessages[errorCode];
    d::stcout << "Error: " << errorMessage << std::endl;
}