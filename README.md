# Advanced File Explorer with Recent Files, Batch Operations, and Custom Themes

A comprehensive console-based file explorer application written in C++ for Linux operating systems. This application provides a complete file management system with navigation, manipulation, search, permission management, and advanced novelty features including recent files history, batch operations, compression support, and customizable UI themes.

## 📋 Project Overview

**Assignment:** Capstone Project - File Explorer Application  
**Language:** C++  
**Platform:** Linux OS  
**Development Time:** 5 Days

## 🎯 Features

### Day 1: Basic Operations
- ✅ List files in current directory (simple and detailed views)
- ✅ Display file information with color coding
- ✅ Show file sizes, modification times, and types

### Day 2: Navigation
- ✅ Change directories (absolute and relative paths)
- ✅ Navigate to parent directory
- ✅ Display current working directory
- ✅ Real-time directory tracking

### Day 3: File Manipulation
- ✅ Create new files
- ✅ Create new directories
- ✅ Delete files and directories (including recursive deletion)
- ✅ Copy files and directories (with full recursive support)
- ✅ Move files and directories (cross-filesystem support)
- ✅ Rename files and directories (separate from move operation)

### Day 4: Search Functionality
- ✅ Recursive file search
- ✅ Case-insensitive filename matching
- ✅ Search in current directory or entire system
- ✅ Display search results with full paths

### Day 5: Permission Management
- ✅ View file permissions (symbolic and octal)
- ✅ Change file permissions (chmod)
- ✅ Change file ownership (chown)
- ✅ Display owner and group information
- ✅ Show detailed file statistics

### ✨ Novelty Features
- ✅ Recent files history tracking (last 10 files)
- ✅ Batch operations (multiple files at once)
- ✅ Zip/Unzip compression support
- ✅ Customizable color themes (default, dark, light)
- ✅ Interactive help and documentation menu
- ✅ Theme-aware UI with dynamic colors

## 🛠️ Prerequisites

- Linux operating system (Ubuntu, Debian, Fedora, etc.)
- G++ compiler (version 4.8 or higher)
- Make utility
- Standard C++ libraries
- `zip` and `unzip` utilities (for compression features)
- Root/sudo access (optional, for some permission operations)

## 📦 Installation

### 1. Clone or Download the Project

```bash
cd /path/to/project
```

### 2. Install Required Utilities

```bash
sudo apt-get update
sudo apt-get install zip unzip
```

### 3. Compile the Application

**Using Make:**
```bash
make
```

**Manual Compilation:**
```bash
g++ -Wall -Wextra -std=c++11 -O2 -o file_explorer file_explorer.cpp
```

### 4. Run the Application

```bash
./file_explorer
```

### 5. Optional: System-wide Installation

```bash
make install
```

This installs the application to `/usr/local/bin/` so you can run it from anywhere:
```bash
file_explorer
```

## 🎮 Usage Guide

### Main Menu Options

The application displays the **current directory** prominently below the title at all times for easy navigation tracking.

```
📂 Navigation & Listing:
  1.  📋 List files (simple)           - Basic file listing with color coding
  2.  📊 List files (detailed)         - Detailed view with permissions, owner, size, dates
  3.  🔄 Change directory              - Navigate to any directory (absolute or relative path)
  4.  ⬆️  Go to parent directory        - Move up one directory level

📁 File Operations:
  5.  ➕ Create file                   - Create a new empty file
  6.  📁 Create directory              - Create a new directory
  7.  🗑️  Delete file/directory         - Remove files or directories (recursive option)
  8.  📄 Copy file/directory           - Copy files or entire directories recursively
  9.  📦 Move file/directory           - Move files/directories to different locations
  10. ✏️  Rename file/directory         - Rename items in the current directory

🔍 Search:
  11. 🔎 Search files                  - Recursively search for files by name

🔐 Permissions Management:
  12. 👁️  View file permissions         - Display detailed permission information
  13. 🔧 Change permissions (chmod)    - Modify file permissions using octal notation
  14. 👤 Change owner/group (chown)    - Change file owner and group

⚙️  Other:
  15. 📍 Display current path          - Show the current working directory

✨ Novelty Features:
  16. 📜 Recent files history          - View last 10 accessed/created files
  17. 📦 Batch operations              - Copy, move, or delete multiple files at once
  18. 🗜️  Zip files/folders             - Compress files and directories
  19. 📂 Unzip files                   - Extract zip archives
  20. 🎨 Change color theme            - Switch between default, dark, and light themes
  21. ❓ Help/Documentation            - Complete guide to all features
  
  0.  ❌ Exit                          - Exit the application
```

### Example Usage Scenarios

#### 1. 📋 List Files (Simple)
```bash
📂 Navigation & Listing:
  1.  📋 List files (simple)
Choose an option: 1

Files in current directory:
📄 document.txt
📁 projects/
📄 readme.md
📁 images/
```

#### 2. 📊 List Files (Detailed)
```bash
Choose an option: 2

Detailed file listing:
-rw-r--r--  1 user group    1024 Nov 15 10:30 📄 document.txt
drwxr-xr-x  2 user group    4096 Nov 15 09:15 📁 projects/
-rw-r--r--  1 user group    2048 Nov 14 16:45 📄 readme.md
drwxr-xr-x  3 user group    4096 Nov 13 14:20 📁 images/
```

#### 3. 🔄 Change Directory
```bash
Choose an option: 3
Enter directory path: /home/user/documents

✅ Successfully changed to: /home/user/documents
Current Directory: /home/user/documents
```

#### 4. ⬆️ Go to Parent Directory
```bash
Choose an option: 4

✅ Successfully moved to parent directory
Current Directory: /home/user
```

#### 5. ➕ Create File
```bash
Choose an option: 5
Enter filename: new_document.txt

✅ File 'new_document.txt' created successfully!
```

#### 6. 📁 Create Directory
```bash
Choose an option: 6
Enter directory name: new_project

✅ Directory 'new_project' created successfully!
```

#### 7. 🗑️ Delete File/Directory
```bash
Choose an option: 7
Enter file/directory name: old_file.txt

✅ File 'old_file.txt' deleted successfully!

# For directories with contents:
Enter file/directory name: old_project/
Directory is not empty. Do you want to delete it recursively? (y/n): y
✅ Directory 'old_project/' deleted recursively!
```

#### 8. 📄 Copy File/Directory
```bash
Choose an option: 8
Enter source file/directory: important_file.txt
Enter destination: backup/important_file_copy.txt

✅ File copied successfully!

# For directories:
Enter source file/directory: project_folder/
Enter destination: backup/project_folder_backup/
✅ Directory copied recursively!
```

#### 9. 📦 Move File/Directory
```bash
Choose an option: 9
Enter source file/directory: document.txt
Enter destination: archive/document.txt

✅ File moved successfully!

# Cross-filesystem move:
Enter source file/directory: large_project/
Enter destination: /mnt/external/large_project/
✅ Directory moved successfully (cross-filesystem)!
```

#### 10. ✏️ Rename File/Directory
```bash
Choose an option: 10
Enter current file/directory name: old_name.txt
Enter new name: new_name.txt

✅ File renamed successfully!
```

#### 11. 🔎 Search Files
```bash
Choose an option: 11
Enter filename to search for: *.txt

Searching for '*.txt'...
Found: ./documents/file1.txt
Found: ./projects/readme.txt
Found: ./backup/notes.txt
Search completed.
```

#### 12. 👁️ View File Permissions
```bash
Choose an option: 12
Enter filename: important_file.txt

File: important_file.txt
Permissions: -rw-r--r-- (644)
Owner: user (1000)
Group: group (1000)
Size: 2048 bytes
Last modified: Nov 15 10:30:45 2023
```

#### 13. 🔧 Change Permissions (chmod)
```bash
Choose an option: 13
Enter filename: script.sh
Enter new permissions (octal, e.g., 755): 755

✅ Permissions changed successfully!
New permissions: -rwxr-xr-x (755)
```

#### 14. 👤 Change Owner/Group (chown)
```bash
Choose an option: 14
Enter filename: shared_file.txt
Enter new owner: newuser
Enter new group: newgroup

✅ Owner and group changed successfully!
```

#### 15. 📍 Display Current Path
```bash
Choose an option: 15

Current working directory: /home/user/projects/current_project
```

#### 16. 📜 Recent Files History
```bash
Choose an option: 16

Recent Files History:
============================================================
1. /home/user/documents/new_document.txt
2. /home/user/projects/test.cpp
3. /home/user/notes/readme.md
============================================================
```

#### 17. 📦 Batch Operations
```bash
Choose an option: 17
Batch operation type:
  1. Delete multiple files
  2. Copy multiple files
  3. Move multiple files
Enter choice: 2

Enter number of files/directories: 3
Enter item 1: file1.txt
Enter item 2: file2.txt
Enter item 3: file3.txt
Enter destination directory: backup/

✅ Batch copy completed!
```

#### 18. 🗜️ Zip Files/Folders
```bash
Choose an option: 18
Enter source file/folder to zip: project_folder
Enter zip filename (e.g., archive.zip): project_backup.zip

✅ Successfully created: project_backup.zip
```

#### 19. 📂 Unzip Files
```bash
Choose an option: 19
Enter zip file to extract: project_backup.zip
Enter destination folder (or '.' for current): extracted/

✅ Successfully extracted to: extracted/
```

#### 20. 🎨 Change Color Theme
```bash
Choose an option: 20
Available themes:
  1. default (Blue/Green/White)
  2. dark (Cyan/Yellow/White)
  3. light (Blue/Green/Magenta)
Enter theme name: dark

✅ Theme changed to: dark
# Menu colors will immediately change!
```

#### 21. ❓ Help/Documentation
```bash
Choose an option: 21

╔════════════════════════════════════════════════════════════╗
║                  FILE EXPLORER - HELP MENU                 ║
╚════════════════════════════════════════════════════════════╝

📖 NAVIGATION & LISTING:
  • List files (simple/detailed) - View all files in current directory
  • Change directory - Navigate to any directory using absolute or relative path
  • Go to parent - Move up one directory level

📂 FILE OPERATIONS:
  • Create - Make new files or directories
  • Delete - Remove files or directories (supports recursive deletion)
  • Copy - Duplicate files/directories (supports recursive copying)
  • Move - Relocate files/directories to different locations
  • Rename - Change the name of files/directories

✨ NOVELTY FEATURES:
  • Recent Files - View history of recently accessed files
  • Batch Operations - Copy, move, or delete multiple files at once
  • Zip/Unzip - Compress and extract .zip archives
  • Color Themes - Choose between default, dark, or light themes
  
... (complete help documentation)
```

#### 0. ❌ Exit
```bash
Choose an option: 0

👋 Thank you for using the File Explorer! Goodbye!
```

## 🎨 Enhanced UI Features

The application includes several UI enhancements for better user experience:

### Visual Elements
- **📍 Current Directory Display**: Always shows your current location prominently below the title
- **🎨 Emoji Icons**: Each menu option has descriptive emojis for quick visual identification
- **🌈 Color Coding**: 
  - **Blue (Bold)** - Directories 📁
  - **Green** - Executable files ⚡
  - **White** - Regular files 📄
  - **Red** - Error messages ❌
  - **Green** - Success messages ✅

### User Experience Features
- **Clear Menu Organization**: Options grouped by functionality (Navigation, File Operations, Search, Permissions)
- **Descriptive Messages**: All operations provide clear feedback with emoji indicators
- **Recursive Operations**: Full support for directory operations with user confirmation
- **Real-time Path Updates**: Current directory shown after navigation changes
- **Recent Files Tracking**: Automatically tracks last 10 files created or accessed
- **Batch Processing**: Handle multiple files in a single operation
- **Compression Support**: Built-in zip/unzip functionality
- **Dynamic Themes**: Switch between color themes on-the-fly
- **White** - Regular files
- **Red** - Error messages
- **Green** - Success messages
- **Yellow** - Warnings and menu headers
- **Cyan** - Information and current path

## 📝 Technical Details

### System Calls Used
- `opendir()`, `readdir()`, `closedir()` - Directory operations
- `stat()` - File information retrieval
- `mkdir()` - Directory creation
- `rmdir()`, `unlink()` - Deletion operations
- `rename()` - Move/rename operations
- `chmod()` - Permission modification
- `chown()` - Ownership modification
- `getcwd()`, `chdir()` - Directory navigation
- `system()` - External command execution (zip/unzip)

### File Permission Format
Permissions are displayed in both symbolic and octal formats:
- **Symbolic:** `drwxr-xr-x` (d=directory, r=read, w=write, x=execute)
- **Octal:** `755` (7=rwx, 5=r-x, 5=r-x)

### Permission Breakdown
```
Owner  Group  Others
rwx    r-x    r-x
421    421    421
 7      5      5
```

## 🔐 Permissions Required

### Standard Operations
- Reading, listing, searching: User read permissions
- Creating, copying files: User write permissions
- Executing, navigating: User execute permissions

### Administrative Operations (require sudo)
- Changing ownership with `chown`
- Modifying permissions on system files
- Accessing restricted directories

## 🐛 Error Handling

The application includes comprehensive error handling for:
- Invalid directory paths
- Permission denied errors
- File not found errors
- Invalid input validation
- Directory deletion of non-empty directories

## 🚀 Advanced Features

### Recursive Search
The search function recursively traverses all subdirectories to find matching files.

### Smart File Sizing
File sizes are automatically formatted with appropriate units (B, KB, MB, GB, TB).

### Safety Confirmations
Destructive operations (like deletion) require user confirmation to prevent accidental data loss.

### Cross-Platform Path Handling
Supports both absolute (`/home/user/file`) and relative (`../folder/file`) paths.

### Recent Files History
Automatically tracks the last 10 files you've created or accessed for quick reference.

### Batch Operations
Process multiple files in a single operation - copy, move, or delete multiple items at once.

### Compression Support
Built-in zip/unzip functionality using system utilities for easy file compression and extraction.

### Customizable Themes
Three color themes to choose from:
- **Default**: Blue/Green/White - Standard vibrant colors
- **Dark**: Cyan/Yellow/Bright White - Optimized for dark terminal backgrounds
- **Light**: Blue/Green/Magenta - Softer colors for light terminal backgrounds

All UI elements (menu, options, file listings) dynamically change with the selected theme.

## 📊 Project Structure

```
File Explorer/
├── file_explorer.cpp    # Main application source code
├── Makefile            # Build configuration
└── README.md           # This file
```

## 🔧 Compilation Options

### Debug Build
```bash
g++ -Wall -Wextra -std=c++11 -g -o file_explorer_debug file_explorer.cpp
```

### Optimized Release Build
```bash
g++ -Wall -Wextra -std=c++11 -O3 -o file_explorer file_explorer.cpp
```

## 📚 Learning Outcomes

This project demonstrates:
1. **Linux System Programming** - Direct interaction with OS through system calls
2. **File System Operations** - Understanding of file system structure and operations
3. **Process Management** - Working with permissions, ownership, and file attributes
4. **C++ Programming** - Object-oriented design, STL usage, and modern C++ features
5. **User Interface Design** - Creating intuitive console-based interfaces with dynamic theming
6. **Error Handling** - Robust error checking and user feedback
7. **External Process Integration** - Integration with system utilities (zip/unzip)
8. **Data Management** - Tracking and managing application state (recent files history)

## 🤝 Day-wise Implementation Guide

### Day 1: Foundation (✅ Complete)
- Application architecture design
- Basic file listing functionality
- Color-coded output system

### Day 2: Navigation (✅ Complete)
- Directory navigation implementation
- Path handling (absolute/relative)
- Current directory tracking

### Day 3: Manipulation (✅ Complete)
- File creation and deletion
- Directory operations
- Copy and move functionality

### Day 4: Search (✅ Complete)
- Recursive search algorithm
- Pattern matching implementation
- Result display formatting

### Day 5: Permissions (✅ Complete)
- Permission viewing system
- chmod implementation
- chown implementation
- User/group information display

### ✨ Novelty Features (✅ Complete)
- Recent files history tracking
- Batch operations for multiple files
- Zip/Unzip compression support
- Dynamic color theme system
- Interactive help documentation

## ⚠️ Important Notes

1. **Root Privileges:** Some operations (like changing ownership or accessing system directories) may require root privileges. Run with `sudo` when necessary.

2. **Empty Directories Only:** The delete operation only works on empty directories. To delete non-empty directories, implement recursive deletion (use with caution).

3. **File Overwriting:** Copy operations will overwrite existing files without warning. Add checks if needed.

4. **Symbolic Links:** The application handles symbolic links but displays them as regular files in simple mode.

5. **Compression Requirements:** The zip/unzip features require `zip` and `unzip` utilities to be installed on your system.

6. **Theme Persistence:** Color theme changes are session-based and will reset to default when the application restarts.

## 🔄 Future Enhancements

Potential improvements:
- Recursive directory deletion ✅ Implemented
- Archive operations (zip) ✅ Implemented (zip)
- Bookmark favorite directories ✅ Implemented (recent files)
- Batch operations ✅ Implemented
- Customizable UI themes ✅ Implemented

## 📄 License

This is an educational project developed as part of a capstone assignment.

## 👨‍💻 Development Information

**Development Period:** 5 Days  
**Testing Platform:** Linux (Ubuntu/Debian compatible)  
**Compiler:** G++ with C++11 standard  

---

## 🎓 Conclusion

This File Explorer application successfully implements all required features across the 5-day development timeline, providing a comprehensive file management solution for Linux systems with an intuitive console-based interface. The addition of novelty features including recent files history, batch operations, compression support, and customizable themes makes this a powerful and user-friendly file management tool.

**Key Achievements:**
- ✅ Complete 5-day implementation with all core features
- ✅ Enhanced with 6 novelty features for improved functionality
- ✅ Dynamic UI with 3 customizable color themes
- ✅ Batch processing for efficient multi-file operations
- ✅ Built-in compression support with zip/unzip
- ✅ Recent files tracking for quick access

**Happy Exploring! 🚀**
