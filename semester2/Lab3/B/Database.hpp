#pragma once

#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

class Message {
public:
  enum class Type {
    news, question, answer, invite, commentOnEvent, commentOnMessage, none
  };

  unsigned id;
  Type type;

  Message() = default;
  Message(unsigned id, Type type): id(id), type(type) {}

  friend std::ostream &operator<<(std::ostream &out, const Message &rhs) {
    out << setw(5) << rhs.id;

    switch (rhs.type) {
      case Type::answer: out            << "   answer           "; break;
      case Type::commentOnEvent: out    << "   commentOnEvent   "; break;
      case Type::commentOnMessage: out  << "   commentOnMessage "; break;
      case Type::invite: out            << "   invite           "; break;
      case Type::news: out              << "   news             "; break;
      case Type::question: out          << "   question         "; break;
      case Type::none: out              << "   none             "; break;

    }
    return out;
  }

};

class Database {
  vector<Message> db;

public:
  void push(const Message &ms) {
    db.push_back(ms);
  }

  const vector<Message> &get() {
    return db;
  }

  void sortById() {
    sorting::radix_sort(db.begin(), db.end(),
             std::function<unsigned (Message &m)>
                     ([](Message &m) -> unsigned {return m.id;}));
  }

  void sortByType() {
    sorting::counting_sort(db.begin(), db.end(), 0, 6,
              std::function<unsigned (Message &m)>
                     ([](Message &m) -> unsigned {return unsigned(m.type);}));
  }

  void generateRandom(size_t size) {
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> randId(0, 100), randType(0, 6);

    db.reserve(size);
    for (int i = 0; i < size; ++i) {
      db.emplace_back(Message(randId(re), Message::Type(randType(re))));
    }
  }


  friend std::ostream &operator<<(std::ostream &out, const Database &rhs) {
    out << "===========================" << endl;
    out << " №   ID   Message type     " << endl;
    out << "---------------------------" << endl;
    for (auto a = rhs.db.begin(); a != rhs.db.end(); ++a) {
      out << setw(2) << a - rhs.db.begin() << *a << endl;
    }
    out << "===========================" << endl;
    return out;
  }
};
