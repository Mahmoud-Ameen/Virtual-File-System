# Project Overview

The file management system project aims to simulate a virtual file system in memory using C++. 
It provides a command-line interface for users to interact with the virtual file system. 
The main goal of the project is to offer basic file management operations such as creating directories, creating files, removing files, removing directories, changing directories, and listing all directories and files.

The file management system will operate entirely in memory and will not perform actual file operations on the disk. 
Instead, it will maintain a tree-like data structure representing the directory hierarchy, where each node in the tree corresponds to a directory or file. 
The system will support navigation through directories, creating new directories and files, removing existing directories and files, and listing the contents of the current directory.

This project serves as a learning exercise for understanding file management concepts and data structures. 
It provides an opportunity to practice working with trees, handling command-line inputs, and implementing basic file management functionalities.

## Functional Requirements

- **Create Directory**: Users should be able to create a new directory within the current directory. 
                        The system should handle duplicate directory names and provide appropriate feedback.

- **Create File**: Users should be able to create a new file within the current directory. 
                    The system should handle duplicate file names and provide appropriate feedback.

- **Remove File**: Users should be able to remove an existing file from the current directory. 
                   If the file doesn't exist, the system should provide an appropriate error message.

- **Remove Directory**: Users should be able to remove an existing directory from the current directory. 
                        If the directory doesn't exist or is not empty, the system should provide an appropriate error message.

- **Change Directory**: Users should be able to navigate to a different directory within the virtual file system. 
                        They should be able to move to the parent directory (using "..") or enter a child directory by specifying its name.

- **List Directories and Files**: Users should be able to list all directories and files within the current directory. 
                                  The system should display the names of directories followed by the names of files.

## Command Descriptions

**Create Directory Command:**

- Command: `mkdir <directory_name>`
- Description: Creates a new directory with the specified name within the current directory.
- Example: `mkdir documents`

**Create File Command:**

- Command: `touch <file_name>`
- Description: Creates a new file with the specified name within the current directory.
- Example: `touch notes.txt`

**Remove File Command:**

- Command: `rm <file_name>`
- Description: Removes the file with the specified name from the current directory.
- Example: `rm notes.txt`

**Remove Directory Command:**

- Command: `rmdir <directory_name>`
- Description: Removes the directory with the specified name from the current directory. The directory must be empty for successful removal.
- Example: `rmdir documents`

**Change Directory Command:**

- Command: `cd <path>`
- Description: Changes the current directory to the specified directory path. Use ".." to move to the parent directory.
- Example: `cd documents`

**List Directories and Files Command:**

- Command: `ls`
- Description: Lists all directories and files within the current directory.
- Example: `ls`

**Rename File Command:**

- Command: `rename <initial_file_name> <new_file_name>`
- Description: Renames the file with the first name to the second name.
- Example: `rename file.txt newfile.txt`

**Rename Directory Command:**

- Command: `renameDir <initial_dir_name> <new_dir_name>`
- Description: Renames the dir with the first name to the second name.
- Example: `renameDir dir.txt newDir.txt`

**List Hierarchy Command:**

- Command: `lsh`
- Description: View the complete hierarchy of directories and files in the current directory.
- Example: `lsh`

**Help Command:**

- Command: `help`
- Description: Shows a list of the available commands.
- Example: `help`



