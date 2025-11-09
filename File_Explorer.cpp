// file_explorer.cpp
// Advanced Linux File Explorer - requires C++17
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sstream>

namespace fs = std::filesystem;
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

static string human_size(uintmax_t size) {
    const char* units[] = {"B","KB","MB","GB","TB"};
    double s = (double)size;
    int i = 0;
    while (s >= 1024.0 && i < 4) { s /= 1024.0; ++i; }
    ostringstream oss;
    oss << fixed << setprecision(2) << s << " " << units[i];
    return oss.str();
}

static string permission_string(const fs::perms p) {
    string s;
    s += (fs::is_directory(p) ? 'd' : '-'); // placeholder; we'll calculate below
    s.clear();
    s += ( (p & fs::perms::owner_read)  != fs::perms::none ) ? 'r' : '-';
    s += ( (p & fs::perms::owner_write) != fs::perms::none ) ? 'w' : '-';
    s += ( (p & fs::perms::owner_exec)  != fs::perms::none ) ? 'x' : '-';
    s += ( (p & fs::perms::group_read)  != fs::perms::none ) ? 'r' : '-';
    s += ( (p & fs::perms::group_write) != fs::perms::none ) ? 'w' : '-';
    s += ( (p & fs::perms::group_exec)  != fs::perms::none ) ? 'x' : '-';
    s += ( (p & fs::perms::others_read)  != fs::perms::none ) ? 'r' : '-';
    s += ( (p & fs::perms::others_write) != fs::perms::none ) ? 'w' : '-';
    s += ( (p & fs::perms::others_exec)  != fs::perms::none ) ? 'x' : '-';
    return s;
}

static string octal_permissions(const fs::perms p) {
    int owner = ((p & fs::perms::owner_read)  != fs::perms::none) << 2 |
                ((p & fs::perms::owner_write) != fs::perms::none) << 1 |
                ((p & fs::perms::owner_exec)  != fs::perms::none);
    int group = ((p & fs::perms::group_read)  != fs::perms::none) << 2 |
                ((p & fs::perms::group_write) != fs::perms::none) << 1 |
                ((p & fs::perms::group_exec)  != fs::perms::none);
    int others= ((p & fs::perms::others_read)  != fs::perms::none) << 2 |
                ((p & fs::perms::others_write) != fs::perms::none) << 1 |
                ((p & fs::perms::others_exec)  != fs::perms::none);
    ostringstream oss;
    oss << owner << group << others;
    return oss.str();
}

struct Entry {
    fs::path path;
    bool is_dir;
    uintmax_t size;
    std::filesystem::file_time_type mtime;
};

enum SortBy { NAME, SIZE, MTIME };

class FileExplorer {
private:
    fs::path current;
    bool showHidden = false;
    SortBy sortBy = NAME;
    bool dirsFirst = true;

public:
    FileExplorer() {
        current = fs::current_path();
    }

    string getCurrentPath() const { return current.string(); }

    void toggleHidden() { showHidden = !showHidden; cout << YELLOW << "Show hidden: " << (showHidden ? "ON" : "OFF") << RESET << endl; }

    void setSort(SortBy s, bool df) { sortBy = s; dirsFirst = df; }

    vector<Entry> readDirectory(const fs::path &p) {
        vector<Entry> res;
        error_code ec;
        if (!fs::exists(p, ec)) {
            cout << RED << "Path does not exist: " << p << RESET << endl;
            return res;
        }
        for (auto &it : fs::directory_iterator(p, fs::directory_options::skip_permission_denied, ec)) {
            string name = it.path().filename().string();
            if (!showHidden && !name.empty() && name[0]=='.') continue;
            Entry e;
            e.path = it.path();
            e.is_dir = it.is_directory(ec);
            e.size = e.is_dir ? 0 : (uintmax_t)fs::file_size(it.path(), ec);
            e.mtime = fs::last_write_time(it.path(), ec);
            res.push_back(move(e));
        }
        sortEntries(res);
        return res;
    }

    void sortEntries(vector<Entry>& entries) {
        sort(entries.begin(), entries.end(), [&](const Entry &a, const Entry &b){
            if (dirsFirst && a.is_dir != b.is_dir) return a.is_dir > b.is_dir;
            if (sortBy == NAME) return a.path.filename().string() < b.path.filename().string();
            if (sortBy == SIZE) return a.size < b.size;
            if (sortBy == MTIME) return a.mtime < b.mtime;
            return a.path.filename().string() < b.path.filename().string();
        });
    }

    void list(bool detailed=false) {
        cout << "\n" << BOLD << CYAN << "Current Directory: " << current << RESET << endl;
        auto entries = readDirectory(current);
        if (detailed) {
            cout << left << setw(12) << "Perms" << setw(8) << "Oct" << setw(12) << "Owner"
                 << setw(12) << "Group" << setw(12) << "Size" << setw(20) << "Modified" << "Name" << endl;
            cout << string(100, '-') << endl;
        }
        for (auto &e : entries) {
            string name = e.path.filename().string();
            error_code ec;
            fs::perms p = fs::status(e.path, ec).permissions();
            // owner/group via stat
            struct stat st;
            string owner = "-", group = "-";
            if (stat(e.path.c_str(), &st) == 0) {
                struct passwd *pw = getpwuid(st.st_uid);
                struct group  *gr = getgrgid(st.st_gid);
                owner = pw ? pw->pw_name : to_string(st.st_uid);
                group = gr ? gr->gr_name : to_string(st.st_gid);
            }
            if (detailed) {
                // permission string
                string perms = permission_string(p);
                string oct = octal_permissions(p);
                // mtime to readable
                auto ftime = fs::last_write_time(e.path, ec);
                std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
                char buf[64];
                strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&cftime));
                cout << left << setw(12) << perms << setw(8) << oct
                     << setw(12) << owner << setw(12) << group
                     << setw(12) << (e.is_dir ? "-" : human_size(e.size))
                     << setw(20) << buf;
            }
            if (e.is_dir) cout << BLUE << name << "/" << RESET << endl;
            else if ((p & fs::perms::owner_exec) != fs::perms::none) cout << GREEN << name << "*" << RESET << endl;
            else cout << WHITE << name << RESET << endl;
        }
    }

    bool changeDirectory(const string &target) {
        fs::path newp = target.empty() ? fs::path(getenv("HOME")) : fs::path(target);
        if (!newp.is_absolute()) newp = current / newp;
        error_code ec;
        newp = fs::weakly_canonical(newp, ec);
        if (ec) {
            cout << RED << "Invalid path: " << target << RESET << endl;
            return false;
        }
        if (!fs::is_directory(newp, ec)) {
            cout << RED << "Not a directory: " << newp << RESET << endl;
            return false;
        }
        current = newp;
        cout << GREEN << "Changed directory to: " << current << RESET << endl;
        return true;
    }

    bool makeDirectory(const string &name) {
        fs::path p = (fs::path(name).is_absolute() ? fs::path(name) : current / name);
        error_code ec;
        if (fs::create_directories(p, ec)) {
            cout << GREEN << "Directory created: " << p << RESET << endl; return true;
        }
        cout << RED << "Failed to create directory: " << p << " (" << ec.message() << ")" << RESET << endl;
        return false;
    }

    bool createFile(const string &name) {
        fs::path p = (fs::path(name).is_absolute() ? fs::path(name) : current / name);
        error_code ec;
        ofstream ofs(p);
        if (!ofs) { cout << RED << "Failed to create file: " << p << RESET << endl; return false; }
        ofs.close();
        cout << GREEN << "File created: " << p << RESET << endl; return true;
    }

    bool previewFile(const string &name, size_t max_lines=20) {
        fs::path p = (fs::path(name).is_absolute() ? fs::path(name) : current / name);
        error_code ec;
        if (!fs::exists(p, ec) || fs::is_directory(p, ec)) { cout << RED << "No such file or it's a directory." << RESET << endl; return false; }
        ifstream ifs(p);
        string line;
        size_t cnt = 0;
        cout << BOLD << CYAN << "----- Preview: " << p << " -----" << RESET << endl;
        while (cnt < max_lines && getline(ifs, line)) {
            cout << line << endl; ++cnt;
        }
        if (!ifs.eof()) cout << YELLOW << "...(truncated)..." << RESET << endl;
        return true;
    }

    bool removeRecursively(const string &name) {
        fs::path p = (fs::path(name).is_absolute() ? fs::path(name) : current / name);
        error_code ec;
        if (!fs::exists(p, ec)) { cout << RED << "Not found: " << p << RESET << endl; return false; }
        cout << YELLOW << "Are you sure you want to delete '" << p << "' recursively? (y/N): " << RESET;
        string ans; getline(cin, ans);
        if (ans != "y" && ans != "Y") { cout << "Aborted." << endl; return false; }
        fs::remove_all(p, ec);
        if (ec) { cout << RED << "Failed to delete: " << ec.message() << RESET << endl; return false; }
        cout << GREEN << "Deleted: " << p << RESET << endl;
        return true;
    }

    bool copyRecursively(const string &src, const string &dst) {
        fs::path s = (fs::path(src).is_absolute() ? fs::path(src) : current / src);
        fs::path d = (fs::path(dst).is_absolute() ? fs::path(dst) : current / dst);
        error_code ec;
        if (!fs::exists(s, ec)) { cout << RED << "Source not found: " << s << RESET << endl; return false; }
        if (fs::is_directory(s, ec)) {
            // replicate directory tree
            for (auto &it : fs::recursive_directory_iterator(s, ec)) {
                fs::path rel = fs::relative(it.path(), s, ec);
                fs::path target = d / rel;
                if (fs::is_directory(it.path(), ec)) fs::create_directories(target, ec);
                else {
                    fs::create_directories(target.parent_path(), ec);
                    fs::copy_file(it.path(), target, fs::copy_options::overwrite_existing, ec);
                    if (ec) cout << RED << "Failed copy: " << it.path() << " -> " << target << " : " << ec.message() << RESET << endl;
                }
            }
        } else {
            fs::create_directories(d.parent_path(), ec);
            fs::copy_file(s, d, fs::copy_options::overwrite_existing, ec);
            if (ec) { cout << RED << "Failed: " << ec.message() << RESET << endl; return false; }
        }
        cout << GREEN << "Copy complete." << RESET << endl;
        return true;
    }

    void searchRecursive(const string &term) {
        cout << CYAN << "Searching recursively for: " << term << " in " << current << RESET << endl;
        error_code ec;
        size_t found=0;
        for (auto &it : fs::recursive_directory_iterator(current, fs::directory_options::skip_permission_denied, ec)) {
            string name = it.path().filename().string();
            if (name.find(term) != string::npos) {
                cout << (it.is_directory()? BLUE : WHITE) << it.path().string() << RESET << endl;
                ++found;
            }
        }
        cout << YELLOW << "Found: " << found << " item(s)." << RESET << endl;
    }

    bool changePermissions(const string &target, const string &mode_str) {
        fs::path p = (fs::path(target).is_absolute() ? fs::path(target) : current / target);
        error_code ec;
        if (!fs::exists(p, ec)) { cout << RED << "Not found: " << p << RESET << endl; return false; }
        // parse octal: e.g., 755
        try {
            int m = stoi(mode_str, nullptr, 8);
            mode_t mode = (mode_t)m;
            if (chmod(p.c_str(), mode) != 0) {
                cout << RED << "chmod failed (require permissions or sudo)." << RESET << endl; return false;
            }
            cout << GREEN << "Permissions changed." << RESET << endl;
            return true;
        } catch (...) {
            cout << RED << "Invalid mode: " << mode_str << RESET << endl;
            return false;
        }
    }

    bool renameItem(const string &oldn, const string &newn) {
        fs::path a = (fs::path(oldn).is_absolute() ? fs::path(oldn) : current / oldn);
        fs::path b = (fs::path(newn).is_absolute() ? fs::path(newn) : current / newn);
        error_code ec;
        fs::rename(a, b, ec);
        if (ec) { cout << RED << "Rename failed: " << ec.message() << RESET << endl; return false; }
        cout << GREEN << "Renamed." << RESET << endl; return true;
    }

    bool moveItem(const string &src, const string &dst) {
        fs::path s = (fs::path(src).is_absolute() ? fs::path(src) : current / src);
        fs::path d = (fs::path(dst).is_absolute() ? fs::path(dst) : current / dst);
        error_code ec;
        fs::create_directories(d.parent_path(), ec);
        fs::rename(s, d, ec);
        if (ec) { cout << RED << "Move/rename failed: " << ec.message() << RESET << endl; return false; }
        cout << GREEN << "Moved." << RESET << endl; return true;
    }
};

void showMenu(const string &cwd) {
    cout << "\n" << BOLD << CYAN << "========= Advanced File Explorer =========" << RESET << endl;
    cout << "Current: " << cwd << endl;
    cout << "1. List (simple)\n2. List (detailed)\n3. Change directory\n4. Toggle hidden files\n5. Create file\n6. Create directory\n7. Delete (recursive)\n8. Copy (recursive)\n9. Move\n10. Rename\n11. Preview file\n12. Search recursively\n13. Change permissions (chmod)\n14. Set sort (name/size/mtime)\n15. Exit\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    FileExplorer explorer;
    while (true) {
        showMenu(explorer.getCurrentPath());
        cout << "Enter choice: ";
        string choice;
        if (!getline(cin, choice)) break;
        if (choice.empty()) continue;

        if (choice == "1") explorer.list(false);
        else if (choice == "2") explorer.list(true);
        else if (choice == "3") {
            cout << "Enter path (abs or relative, blank => HOME): ";
            string p; getline(cin, p);
            explorer.changeDirectory(p);
        } else if (choice == "4") explorer.toggleHidden();
        else if (choice == "5") {
            cout << "Filename: "; string f; getline(cin,f); explorer.createFile(f);
        } else if (choice == "6") {
            cout << "Directory name: "; string d; getline(cin,d); explorer.makeDirectory(d);
        } else if (choice == "7") {
            cout << "Item to delete (path): "; string t; getline(cin,t); explorer.removeRecursively(t);
        } else if (choice == "8") {
            cout << "Source: "; string s; getline(cin,s);
            cout << "Destination: "; string d; getline(cin,d);
            explorer.copyRecursively(s,d);
        } else if (choice == "9") {
            cout << "Source: "; string s; getline(cin,s);
            cout << "Destination: "; string d; getline(cin,d);
            explorer.moveItem(s,d);
        } else if (choice == "10") {
            cout << "Current name: "; string a; getline(cin,a);
            cout << "New name: "; string b; getline(cin,b);
            explorer.renameItem(a,b);
        } else if (choice == "11") {
            cout << "File to preview: "; string f; getline(cin,f);
            explorer.previewFile(f, 30);
        } else if (choice == "12") {
            cout << "Search term: "; string t; getline(cin,t);
            explorer.searchRecursive(t);
        } else if (choice == "13") {
            cout << "Target file: "; string tf; getline(cin,tf);
            cout << "Mode (octal e.g. 755): "; string m; getline(cin,m);
            explorer.changePermissions(tf, m);
        } else if (choice == "14") {
            cout << "Sort by (name/size/mtime): "; string s; getline(cin,s);
            bool df=true;
            cout << "Directories first? (y/N): "; string q; getline(cin,q);
            if (q=="y"||q=="Y") df=true; else df=false;
            if (s=="name") explorer.setSort(NAME, df);
            else if (s=="size") explorer.setSort(SIZE, df);
            else if (s=="mtime") explorer.setSort(MTIME, df);
            else cout << RED << "Unknown sort option" << RESET << endl;
        } else if (choice == "15") {
            cout << GREEN << "Goodbye!" << RESET << endl; break;
        } else {
            cout << RED << "Invalid option" << RESET << endl;
        }
        cout << "\nPress Enter to continue..."; string dummy; getline(cin, dummy);
    }
    return 0;
}
