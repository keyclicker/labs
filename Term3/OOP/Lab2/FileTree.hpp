#pragma once
#include <filesystem>
#include <sstream>
#include <chrono>
#include <string>
#include <vector>
#include <map>

namespace fs = std::filesystem;
using namespace std::chrono_literals;

class FileTree {
private:
    bool isDirectory = true;
    bool isVirtual = true;

    size_t fileSize;
    std::string mtime;
    std::string name;
    std::string type;
    std::string path;

    std::vector<FileTree*> forest;
    std::map<std::string, std::string> metadata;

    template<typename T>
    static std::string dateToString(const T &time) {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(time - T::clock::now()
                  + system_clock::now());
        auto tt = system_clock::to_time_t(sctp);

        std::tm *gmt = std::gmtime(&tt);
        std::stringstream buffer;
        buffer << std::put_time(gmt, "%X, %d.%m.%y");
        return buffer.str();
    }

public:
    static auto Virtual(const std::string &name){
        auto ft = new FileTree;
        ft->isVirtual = true;
        ft->isDirectory = true;
        ft->name = name;
        ft->mtime = dateToString(std::chrono::system_clock::now());
        ft->type = "Virtual Directory";
        ft->path = "None";
        return ft;
    }

    FileTree() {}

    FileTree(const std::string &patharg) {
        auto fspath = fs::path(patharg);
        isVirtual = false;
        path = fs::absolute(fspath);
        name = fspath.filename();
        isDirectory = fs::is_directory(fspath);

        mtime = dateToString(fs::last_write_time(fspath));

        if (!isDirectory) {
            fileSize = fs::file_size(fspath);
            type = fspath.extension();
        }
        else {
            type = "Directory";
            fileSize = 0;
            for (auto &p: fs::directory_iterator(fspath)) {
                auto ft = new FileTree(fs::absolute(p));
                fileSize += ft->fileSize;
                forest.emplace_back(ft);
            }
        }
    }

    FileTree *addDir(const std::string &patharg) {
        forest.emplace_back(new FileTree(fs::absolute(patharg)));
        return forest.back();
    }

    FileTree *addVirtualDir(const std::string &name) {
        forest.emplace_back(FileTree::Virtual(name));
        return forest.back();
    }

    bool getIsDirectory() const;
    bool getIsVirtual() const;

    size_t getFileSize() const;
    std::string getMtime() const;

    void setName(const std::string &value);
    std::string getName() const;
    std::string getType() const;
    std::string getPath() const;

    std::vector<FileTree*> getForest() const;

    void clearFields();
    void insertField(const std::string &field, const std::string &value);
    std::map<std::string, std::string> getMetadata() const;
};
