cmake_minimum_required(VERSION 3.12)
project(FileManagementSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(FileManagementSystem
        src/UserInterface.cpp
        src/CommandProcessor.cpp
        src/FileSystemDataStructure.cpp
        src/FileSystemOperations.cpp
        src/ErrorHandling.cpp
        src/main.cpp)

target_include_directories(FileManagementSystem PUBLIC include)
