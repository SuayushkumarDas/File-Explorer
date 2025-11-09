Linux File Explorer Application
A console-based File Explorer written in C++ for Linux systems.
This project provides a complete file management system that supports navigation, file manipulation, search, and permission management directly through the terminal.

Project Overview
Project Type: Capstone Project
Language Used: C++
Operating System: Linux Development Time: 5 Days
Features Overview
Day 1: Basic Operations
List files in the current directory (simple and detailed view)
Display file permissions, size, owner, group, and modification time
Color-coded display for directories, executables, and regular files
Day 2: Navigation
Change directories (absolute and relative paths)
Navigate to the parent directory
Display the current working directory
Real-time path tracking
Day 3: File Manipulation
Create files and directories
Delete files and directories (with recursive option)
Copy files and directories recursively
Move files or directories (supports cross-filesystem operations)
Rename files or directories
Day 4: Search Functionality
Recursive file search across directories
Case-insensitive search
Display full file paths for all search results
Day 5: Permission Management
View file permissions in symbolic and octal format
Change permissions using the chmod command
Change ownership and group using the chown command
Display owner, group, size, and last modification time
Prerequisites
Linux environment (Ubuntu, Debian, Fedora, or WSL)
Installed g++ compiler
Installed make utility
Root or sudo privileges (for permission and ownership operations)
Installation and Setup
Step 1: Clone or Download the Repository
git clone https://github.com/<your-username>/file-explorer-cpp.git
cd file-explorer-cpp
Step 2: Compile the Application
Using Makefile:

make
Manual Compilation:

g++ -Wall -Wextra -std=c++17 -O2 -o file_explorer file_explorer.cpp
Step 3: Run the Application
./file_explorer
Step 4: Optional Global Installation
sudo cp file_explorer /usr/local/bin/
file_explorer
Application Menu
==================== FILE EXPLORER MENU ====================
Current Directory: /home/user
------------------------------------------------------------
1.  List files (simple)
2.  List files (detailed)
3.  Change directory
4.  Go to parent directory
5.  Create file
6.  Create directory
7.  Delete file/directory
8.  Copy file
9.  Move file
10. Rename file/directory
11. Search files
12. View file permissions
13. Change permissions (chmod)
14. Change owner/group (chown)
15. Display current path
0.  Exit
------------------------------------------------------------
Example Usage
List Files
Choose an option: 1
Documents/
Projects/
readme.txt
Detailed File Listing
Choose an option: 2
Permissions  Owner   Group   Size     Modified             Name
-rw-r--r--   user    user    2.0 KB   2025-11-09 10:15:21 readme.txt
drwxr-xr-x   user    user    4.0 KB   2025-11-09 10:00:10 Projects/
Change Directory
Choose an option: 3
Enter directory: Projects
Changed directory to: /home/user/Projects
Create File
Choose an option: 5
Enter filename: new.txt
File created successfully.
Delete File
Choose an option: 7
Enter file/directory: old.txt
File deleted successfully.
Copy File
Choose an option: 8
Enter source: new.txt
Enter destination: backup.txt
File copied successfully.
Move File
Choose an option: 9
Enter source: backup.txt
Enter destination: archive.txt
File moved successfully.
Rename File
Choose an option: 10
Enter current name: archive.txt
Enter new name: final.txt
File renamed successfully.
Search Files
Choose an option: 11
Enter search term: read
Search results:
./readme.txt
./Documents/read.txt
View File Permissions
Choose an option: 12
Enter filename: final.txt
Permissions: -rw-r--r--
Owner: user
Group: user
Size: 1.2 KB
Last Modified: 2025-11-09 10:30:11
User Interface Highlights
Clear and structured menu layout
Color-coded file output
Real-time directory updates
Informative feedback messages
Safe user confirmations before delete operation
System Calls Used
opendir(), readdir(), closedir() – Directory operations
stat() – Retrieve file metadata
mkdir(), rmdir(), unlink() – File and directory creation/deletion
rename() – Move or rename files
chmod() – Change permissions
chown() – Change ownership
getcwd(), chdir() – Directory management
Permission Representation
Format	Example
Symbolic	drwxr-xr-x
Octal	755
Folder Structure
file-explorer-cpp/
 ├── file_explorer.cpp    # Main source file
 ├── Makefile             # Build automation file
 ├── README.md            # Project documentation
 └── LICENSE              # Project license file
Build Options
Debug Mode

g++ -Wall -Wextra -std=c++17 -g -o file_explorer_debug file_explorer.cpp
Optimized Release

g++ -Wall -Wextra -std=c++17 -O3 -o file_explorer file_explorer.cpp
Learning Outcomes
This project demonstrates:

File and directory management using C++ and Linux system calls
Understanding of permissions and ownership in Linux
Implementation of recursive algorithms for search and copy operations
Structured and modular C++ class design
Clean terminal UI with clear feedback messages
Proper error handling and safe user interactions
Future Enhancements
Add file content preview
Implement file sorting and filtering
Support for zip/tar archiving
Directory bookmarks and navigation history
File comparison and difference checking
Developer Information
Developer: Subham Nayak Role: C++ Developer Platform: Ubuntu (Linux) Compiler: g++ (GNU C++ Compiler)

License
This project is licensed under the MIT License. You are free to use, modify, and distribute it for educational or personal purposes.

Conclusion
The Linux File Explorer Application provides a complete, interactive, and reliable file management system built entirely with C++. It showcases deep understanding of Linux system calls, file permissions, and terminal interface design. This project serves as a solid demonstration of both system-level programming and C++ object-oriented implementation.

