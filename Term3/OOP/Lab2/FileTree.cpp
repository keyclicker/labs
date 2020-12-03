#include "FileTree.hpp"


bool FileTree::getIsVirtual() const {
    return isVirtual;
}

size_t FileTree::getFileSize() const {
    return fileSize;
}

std::string FileTree::getMtime() const {
    return mtime;
}

std::string FileTree::getName() const {
    return name;
}

std::string FileTree::getType() const {
    return type;
}

std::string FileTree::getPath() const {
    return path;
}

std::vector<FileTree*> FileTree::getForest() const {
    return forest;
}

void FileTree::clearFields()
{
    metadata.clear();
}

void FileTree::insertField(const std::string &field, const std::string &value)
{
    metadata[field] = value;
}

std::map<std::string, std::string> FileTree::getMetadata() const {
    return metadata;
}

void FileTree::setName(const std::string &value)
{
    name = value;
}

bool FileTree::getIsDirectory() const {
    return isDirectory;
}
