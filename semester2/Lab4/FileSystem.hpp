#pragma once
#include <string>
#include <vector>
#include <memory>


class FileObject {
private:
  uint64_t size; //in bytes
  std::vector<FileObject> dir;
  std::string name;
  FileObject *parent;

  enum class Type { File, Directory };
  Type type;

public:
  //Task 8
  void print() {
    // i've got some encoding problem with
    // '│' sign when i using char instead  string
    static std::list<std::string> tree;

    if (tree.empty()) {
      update();
      std::cout << "Root: ";
    }
    else std::cout << " ";

    std::cout << std::setw(0) << name
            << std::setw(6) << size << " byte"
              << std::endl;

    if (!dir.empty()) {
      for (auto a = dir.begin(); a != --dir.end(); ++a) {
        for (auto &a : tree)
          std::cout << a;
        tree.insert(tree.end(), {"│", " ", " ", " ", " ", " "});

        std::cout << "├────";
        a->print();

        for (int i = 0; i < 6; ++i)
          tree.pop_back();
      }

      for (auto &a : tree)
        std::cout << a;
      tree.insert(tree.end(), {" ", " ", " ", " ", " ", " "});

      std::cout << "└────";
      dir.back().print();

      for (int i = 0; i < 6; ++i)
        tree.pop_back();
    }
  }

  void update() {
    if (type == Type::Directory) {
      for (auto &a : dir)
        a.update();
      size = 0;
      for (auto &a : dir)
        size += a.size;
    }
  }

  void genRandom(size_t sz) {
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int>
            randsize(sz/4, sz/2), randsizeb(1024, 32768),
            randtype(0, 3), randname(0, 16), randf(0, 8);

    type = Type(randtype(re) ?  Type::Directory : Type::File);

    name = std::vector<std::string>(
            {"Lorem", "ipsum", "dolor", "sit", "amet",
             "consectetur", "adipiscing", "elit", "sed",
             "do", "eiusmod", "tempor", "incididunt",
             "ut", "labore", "magna", "aliqua"}) [randname(re)];

    if (type == Type::File) {
      size = randsizeb(re);
      name.append(std::vector<std::string>(
              {".jpeg", ".dat", ".rar", ".zip",
               ".bin", ".mp3", ".mkv", ".avi"}) [randf(re)]);
    }
    else {
      auto rs = randsize(re);
      dir.reserve(rs);

      for (int i = 0; i < rs; ++i) {
        dir.emplace_back(FileObject());
        dir.back().genRandom(sz - rs);
      }
    }
  }
};