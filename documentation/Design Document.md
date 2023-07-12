# Design Document

## 1. Architecture Overview

The file management system is designed with a layered architecture, 
separating the user interface, command processing, file system operations, and error handling into distinct components. 
This modular architecture promotes separation of concerns and allows for flexibility and extensibility in each component.

## 2. Components Description

### Client (User Interface)

The client component is responsible for interacting with the user, receiving commands, and displaying outputs. 
It provides a command-line interface (CLI) for users to interact with the file management system. 
The user interface parses user input, invokes the appropriate commands, and displays the results or error messages.

### Server (Core Components)

The server component consists of the following core components:

#### Command Processor

The Command Processor receives user commands from the User Interface and interprets them. 
It maps each command to the corresponding action in the File System Operations component. 
The Command Processor coordinates the execution of the requested operations, validates input, and handles any errors or exceptions that may occur.

#### File System Data Structure

The File System Data Structure represents the virtual file system in memory. 
It manages the hierarchical structure of directories and files using a tree-like data structure. 
Each node in the tree represents a directory or file and contains information such as the name, type, and references to child nodes. 
The File System Data Structure provides methods for traversing the tree, adding directories/files, removing directories/files, and retrieving information about directories and files.

#### File System Operations

The File System Operations component encapsulates the logic for performing file system operations based on user commands. 
It interacts with the File System Data Structure to manipulate the tree-like structure and update it accordingly. 
The File System Operations include functions and methods for creating directories, creating files, removing files, removing directories, changing directories, and listing directories/files. 
It handles the business logic behind each operation, ensures the integrity of the file system structure, and communicates with the Command Processor and User Interface components.

#### Error Handling

The Error Handling component handles and reports errors that occur during command processing or file system operations. 
It receives error messages from other components, such as the File System Operations or the File System Data Structure, and communicates them back to the User Interface for appropriate display. 
The Error Handling component ensures that users receive meaningful error messages when they encounter issues, such as invalid commands, non-existent directories/files, or operations on read-only directories/files.
