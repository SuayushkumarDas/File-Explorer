#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <iomanip>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

class FileExplorer {
private:
    string currentPath;

    string getPermissionsString(mode_t mode) {
        string perms = "";
        perms += (S_ISDIR(mode)) ? "d" : "-";
        perms += (mode & S_IRUSR) ? "r" : "-";
        perms += (mode & S_IWUSR) ? "w" : "-";
        perms += (mode & S_IXUSR) ? "x" : "-";
        perms += (mode & S_IRGRP) ? "r" : "-";
        perms += (mode & S_IWGRP) ? "w" : "-";
        perms += (mode & S_IXGRP) ? "x" : "-";
        perms += (mode & S_IROTH) ? "r" : "-";
        perms += (mode & S_IWOTH) ? "w" : "-";
        perms += (mode & S_IXOTH) ? "x" : "-";
        return perms;
    }

    string formatFileSize(off_t size) {
        const char* units[] = {"B", "KB", "MB", "GB"};
        double fsize = size;
        int i = 0;
        while (fsize >= 1024 && i < 3) {
            fsize /= 1024;
            i++;
        }
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.2f %s", fsize, units[i]);
        return string(buffer);
    }

    string getModificationTime(time_t mtime) {
        char buffer[100];
        struct tm* timeinfo = localtime(&mtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }

public:
    FileExplorer() {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        currentPath = string(cwd);
    }

    string getCurrentPath() const { return currentPath; }

    void listFiles(bool detailed = false) {
        DIR* dir = opendir(currentPath.c_str());
        if (!dir) {
            cout << RED << "Error: Cannot open directory." << RESET << endl;
            return;
        }

        struct dirent* entry;
        vector<pair<string, bool>> entries;
        while ((entry = readdir(dir)) != NULL) {
            string name = entry->d_name;
            string fullPath = currentPath + "/" + name;
            struct stat fileStat;
            stat(fullPath.c_str(), &fileStat);
            entries.push_back({name, S_ISDIR(fileStat.st_mode)});
        }
        closedir(dir);

        sort(entries.begin(), entries.end(), [](auto &a, auto &b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });

        cout << "\n" << BOLD << CYAN << "Current Directory: " << currentPath << RESET << endl;
        cout << string(80, '=') << endl;

        if (detailed) {
            cout << left << setw(12) << "Permissions" << setw(10) << "Owner"
                 << setw(10) << "Group" << setw(12) << "Size"
                 << setw(20) << "Modified" << "Name" << endl;
            cout << string(80, '-') << endl;
        }

        for (auto &entry : entries) {
            string name = entry.first;
            string fullPath = currentPath + "/" + name;
            struct stat fileStat;
            stat(fullPath.c_str(), &fileStat);

            if (detailed) {
                struct passwd* pw = getpwuid(fileStat.st_uid);
                struct group* gr = getgrgid(fileStat.st_gid);
                cout << left << setw(12) << getPermissionsString(fileStat.st_mode)
                     << setw(10) << (pw ? pw->pw_name : to_string(fileStat.st_uid))
                     << setw(10) << (gr ? gr->gr_name : to_string(fileStat.st_gid))
                     << setw(12) << formatFileSize(fileStat.st_size)
                     << setw(20) << getModificationTime(fileStat.st_mtime);
            }

            if (S_ISDIR(fileStat.st_mode))
                cout << BLUE << name << "/" << RESET << endl;
            else if (fileStat.st_mode & S_IXUSR)
                cout << GREEN << name << "*" << RESET << endl;
            else
                cout << WHITE << name << RESET << endl;
        }
    }

    void changeDirectory(const string &path) {
        string newPath;
        if (path == "..") {
            size_t pos = currentPath.find_last_of('/');
            newPath = (pos == 0) ? "/" : currentPath.substr(0, pos);
        } else newPath = currentPath + "/" + path;

        if (chdir(newPath.c_str()) == 0) {
            currentPath = newPath;
            cout << GREEN << "Changed directory to: " << currentPath << RESET << endl;
        } else cout << RED << "Error: Directory not found." << RESET << endl;
    }

    void createFile(const string &filename) {
        ofstream file(currentPath + "/" + filename);
        if (file.is_open()) {
            file.close();
            cout << GREEN << "File created: " << filename << RESET << endl;
        } else cout << RED << "Error creating file." << RESET << endl;
    }

    void createDirectory(const string &dirname) {
        if (mkdir((currentPath + "/" + dirname).c_str(), 0755) == 0)
            cout << GREEN << "Directory created: " << dirname << RESET << endl;
        else cout << RED << "Error creating directory." << RESET << endl;
    }

    void deleteItem(const string &name) {
        string path = currentPath + "/" + name;
        struct stat s;
        if (stat(path.c_str(), &s) != 0) {
            cout << RED << "Item not found." << RESET << endl;
            return;
        }
        if (S_ISDIR(s.st_mode)) {
            if (rmdir(path.c_str()) == 0)
                cout << GREEN << "Directory deleted." << RESET << endl;
            else cout << RED << "Error deleting directory." << RESET << endl;
        } else {
            if (unlink(path.c_str()) == 0)
                cout << GREEN << "File deleted." << RESET << endl;
            else cout << RED << "Error deleting file." << RESET << endl;
        }
    }

    void copyFile(const string &src, const string &dest) {
        ifstream in(currentPath + "/" + src, ios::binary);
        ofstream out(currentPath + "/" + dest, ios::binary);
        if (!in || !out) {
            cout << RED << "Error copying file." << RESET << endl;
            return;
        }
        out << in.rdbuf();
        cout << GREEN << "File copied from " << src << " to " << dest << RESET << endl;
    }

    void moveFile(const string &src, const string &dest) {
        string srcPath = currentPath + "/" + src;
        string destPath = currentPath + "/" + dest;
        if (rename(srcPath.c_str(), destPath.c_str()) == 0)
            cout << GREEN << "File moved successfully." << RESET << endl;
        else
            cout << RED << "Error moving file." << RESET << endl;
    }

    void renameItem(const string &oldName, const string &newName) {
        string oldPath = currentPath + "/" + oldName;
        string newPath = currentPath + "/" + newName;
        if (rename(oldPath.c_str(), newPath.c_str()) == 0)
            cout << GREEN << "Item renamed successfully." << RESET << endl;
        else
            cout << RED << "Error renaming item." << RESET << endl;
    }

    void searchFiles(const string &term) {
        DIR* dir = opendir(currentPath.c_str());
        if (!dir) return;
        struct dirent* entry;
        cout << "\nSearch results for \"" << term << "\":" << endl;
        cout << string(50, '-') << endl;
        while ((entry = readdir(dir)) != NULL) {
            string name = entry->d_name;
            if (name.find(term) != string::npos)
                cout << name << endl;
        }
        closedir(dir);
    }

    void viewPermissions(const string &filename) {
        string fullPath = currentPath + "/" + filename;
        struct stat fileStat;
        if (stat(fullPath.c_str(), &fileStat) != 0) {
            cout << RED << "File not found." << RESET << endl;
            return;
        }
        cout << "Permissions: " << getPermissionsString(fileStat.st_mode) << endl;
        cout << "Owner: " << getpwuid(fileStat.st_uid)->pw_name << endl;
        cout << "Group: " << getgrgid(fileStat.st_gid)->gr_name << endl;
        cout << "Size: " << formatFileSize(fileStat.st_size) << endl;
        cout << "Last Modified: " << getModificationTime(fileStat.st_mtime) << endl;
    }

    void changePermissions(const string &filename, const string &modeStr) {
        mode_t mode = stoi(modeStr, nullptr, 8);
        if (chmod((currentPath + "/" + filename).c_str(), mode) == 0)
            cout << GREEN << "Permissions changed successfully." << RESET << endl;
        else
            cout << RED << "Error changing permissions." << RESET << endl;
    }

    void changeOwner(const string &filename, const string &user, const string &group) {
        struct passwd *pw = getpwnam(user.c_str());
        struct group *gr = getgrnam(group.c_str());
        if (!pw || !gr) {
            cout << RED << "Invalid user or group." << RESET << endl;
            return;
        }
        if (chown((currentPath + "/" + filename).c_str(), pw->pw_uid, gr->gr_gid) == 0)
            cout << GREEN << "Owner/Group changed successfully." << RESET << endl;
        else
            cout << RED << "Error changing owner/group (may require sudo)." << RESET << endl;
    }
};

void displayMenu(const string &path) {
    cout << "\n" << BOLD << CYAN << "==================== FILE EXPLORER MENU ====================" << RESET << endl;
    cout << BOLD << "Current Directory: " << RESET << path << endl;
    cout << string(60, '-') << endl;
    cout << "1.  List files (simple)\n";
    cout << "2.  List files (detailed)\n";
    cout << "3.  Change directory\n";
    cout << "4.  Go to parent directory\n";
    cout << "5.  Create file\n";
    cout << "6.  Create directory\n";
    cout << "7.  Delete file/directory\n";
    cout << "8.  Copy file\n";
    cout << "9.  Move file\n";
    cout << "10. Rename file/directory\n";
    cout << "11. Search files\n";
    cout << "12. View file permissions\n";
    cout << "13. Change permissions (chmod)\n";
    cout << "14. Change owner/group (chown)\n";
    cout << "15. Display current path\n";
    cout << "0.  Exit\n";
    cout << string(60, '-') << endl;
}

int main() {
    FileExplorer explorer;
    int choice;
    string input1, input2, input3;

    cout << "\n" << string(60, '=') << endl;
    cout << BOLD << CYAN << "              FILE EXPLORER APPLICATION" << RESET << endl;
    cout << BOLD << GREEN << "       Linux File Management System (C++)" << RESET << endl;
    cout << string(60, '=') << endl;

    while (true) {
        displayMenu(explorer.getCurrentPath());
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: explorer.listFiles(false); break;
            case 2: explorer.listFiles(true); break;
            case 3:
                cout << "Enter directory name: ";
                getline(cin, input1);
                explorer.changeDirectory(input1);
                break;
            case 4: explorer.changeDirectory(".."); break;
            case 5:
                cout << "Enter filename: ";
                getline(cin, input1);
                explorer.createFile(input1);
                break;
            case 6:
                cout << "Enter directory name: ";
                getline(cin, input1);
                explorer.createDirectory(input1);
                break;
            case 7:
                cout << "Enter item to delete: ";
                getline(cin, input1);
                explorer.deleteItem(input1);
                break;
            case 8:
                cout << "Enter source filename: ";
                getline(cin, input1);
                cout << "Enter destination filename: ";
                getline(cin, input2);
                explorer.copyFile(input1, input2);
                break;
            case 9:
                cout << "Enter source filename: ";
                getline(cin, input1);
                cout << "Enter destination filename: ";
                getline(cin, input2);
                explorer.moveFile(input1, input2);
                break;
            case 10:
                cout << "Enter current name: ";
                getline(cin, input1);
                cout << "Enter new name: ";
                getline(cin, input2);
                explorer.renameItem(input1, input2);
                break;
            case 11:
                cout << "Enter search term: ";
                getline(cin, input1);
                explorer.searchFiles(input1);
                break;
            case 12:
                cout << "Enter filename: ";
                getline(cin, input1);
                explorer.viewPermissions(input1);
                break;
            case 13:
                cout << "Enter filename: ";
                getline(cin, input1);
                cout << "Enter permission (e.g., 755): ";
                getline(cin, input2);
                explorer.changePermissions(input1, input2);
                break;
            case 14:
                cout << "Enter filename: ";
                getline(cin, input1);
                cout << "Enter owner username: ";
                getline(cin, input2);
                cout << "Enter group name: ";
                getline(cin, input3);
                explorer.changeOwner(input1, input2, input3);
                break;
            case 15:
                cout << CYAN << "Current path: " << explorer.getCurrentPath() << RESET << endl;
                break;
            case 0:
                cout << GREEN << "Exiting File Explorer. Goodbye!" << RESET << endl;
                return 0;
            default:
                cout << RED << "Invalid choice!" << RESET << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}
