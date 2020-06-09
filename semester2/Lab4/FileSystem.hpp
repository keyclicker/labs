#pragma once
#include <string>
#include <vector>
#include <memory>

struct Time {
  uint8_t day, month;
  uint16_t year;

  Time(uint16_t day = 0, uint16_t month = 0, uint16_t year = 0) :
  day(day), month(month), year(year) {}

  bool operator==(const Time &rhs) const {
    return day == rhs.day && month == rhs.month && year == rhs.year;
  }
  bool operator!=(const Time &rhs) const {
    return day != rhs.day || month != rhs.month || year != rhs.year;
  }
  bool operator<(const Time &rhs) const {
    if (year < rhs.year)
      return true;
    else if (year == rhs.year) {
      if (month < rhs.month)
        return true;
      else if (month == rhs.month)
        if (day < rhs.day)
          return true;
    }
    return false;
  }
  bool operator<=(const Time &rhs) const {
    return operator<(rhs) && operator==(rhs);
  }
  bool operator>=(const Time &rhs) const {
    return !operator<(rhs);
  }
  bool operator>(const Time &rhs) const {
    return !operator<(rhs) && operator!=(rhs);
  }

  friend std::ostream &operator<<(std::ostream &out, const Time& t) {
    if (t == Time()) {
      out << "  nan  ";
    }
    else {
      out << std::setfill('0');
      out << std::setw(2) << int(t.day) << '.'
         << std::setw(2) << int(t.month) << '.' << t.year;
      out << std::setfill(' ');
    }
    return out;
  }
};

//Task 26
class FileObject {
public:
  enum class Type { File, Directory };
private:
  Type type;
  uint64_t size = 0; //in bytes
  Time modified, minModified;
  std::string name;
  std::vector<FileObject> dir;

public:
  Time getMaxTime() const{
    return modified;
  }
  Time getMinTime() const{
    return minModified;
  }
  Type getType() const {
    return type;
  }
  uint64_t getSize() const {
    return size;
  }
  const string &getName() const {
    return name;
  }
  const vector<FileObject> &getDir() const {
    return dir;
  }

  template<typename Predicate>
  Time removeIf(Predicate predicate) {
    static int depth = -1;
    depth++;
    for (auto &a : dir)
      a.removeIf(predicate);
    dir.erase(std::remove_if(dir.begin(), dir.end(), predicate), dir.end());
    if (depth-- == 0) update();
  }

  template<typename Predicate>
  FileObject getIf(Predicate predicate) {
    auto cleared = *this;
    cleared.removeIf([predicate](const FileObject &fo){return !predicate(fo);});
    return cleared;
  }

  void update() {
    if (type == Type::Directory) {
      for (auto &a : dir)
        a.update();
      size = 0;
      for (auto &a : dir) {
        size += a.size;
      }

      if (!dir.empty()) {
        modified = std::max_element(dir.begin(), dir.end(),
        [](const FileObject &a, FileObject &b)
        { return a.modified < b.modified; })->modified;

        minModified = std::min_element(dir.begin(), dir.end(),
        [](const FileObject &a, FileObject &b)
        { return a.minModified < b.minModified
        && a.minModified != Time(); })->minModified;
      }
    }
  }

  void print() {
    static std::list<std::string> tree;

    if (tree.empty()) {
      std::cout << "       Name    Size      Modified"
                   "\nRoot: ";
    }
    else std::cout << " ";

    std::cout << std::setw(0) << name
            << std::setw(7) << size << " byte  "
            << modified
              << std::endl;

    if (!dir.empty()) {
      for (auto a = dir.begin(); a != --dir.end(); ++a) {
        for (auto &a : tree)
          std::cout << a;
        tree.emplace_back("│     ");

        std::cout << "├────";
        a->print();
        tree.pop_back();
      }

      for (auto &a : tree)
        std::cout << a;
      tree.emplace_back("      ");

      std::cout << "└────";
      dir.back().print();
      tree.pop_back();
    }
  }

  void genRandom(size_t sz) {
    static int16_t depth = -1;
    depth++;

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int>
            randsize(sz/4, sz/2), randsizeb(1024, 32768),
            randtype(0, 1), randname(0, 16), randf(0, 7),
            randyear(2013, 2020), randmonth(1, 12), randday(1, 30);

    if (depth < 2)
      type = Type::Directory;
    else
      type = Type(randtype(re));

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

      modified.year = randyear(re);
      modified.month = randmonth(re);
      modified.day = randday(re);
      minModified = modified;
    }
    else {
      auto rs = randsize(re);
      dir.reserve(rs);

      for (int i = 0; i < rs; ++i) {
        dir.emplace_back(FileObject());
        dir.back().genRandom(sz - rs);
      }
    }
    depth--;
    if (depth == -1) update();
  }
};