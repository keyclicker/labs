#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "Time.hpp"
#include "Database.hpp"
#include "../sorting.hpp"

class Message {
public:
  enum class Type {
    news, question, answer, invite, commentOnEvent, commentOnMessage, none
  };

  void loadFromTextFile(std::ifstream &in);
  void saveToTextFile(std::ofstream &out) const;

  void loadFromBinFile(std::ifstream &in);
  void saveToBinFile(std::ofstream &out) const;

  void print() const;
  void printCompact() const;

  static Message Generate();

  std::string senderLogin;
  std::string receiverLogin;
  std::string text;
  Time time;
  float spamProbability;
  uint16_t senderID;
  Type type;

  static std::string typetos(Type val);
  static Type stotype(const std::string &val);
};

template<>
class Database<Message> : public BaseDatabase<Message>{
public:
  static Database<Message> Generate(size_t size);

  Database<Message> contains(const std::string &text) const;
  Database<Message> ofSender(const std::string &sender) const;
  Database<Message> ofReceiver(const std::string &receiver) const;
  Database<Message> inSpamRange(double r1, double r2) const;
  Database<Message> ofType(Message::Type type) const;
  Database<Message> sentBefore(const Time &time) const;
  Database<Message> sentAfter(const Time &time) const;
  Database<Message> inTimeRange(const Time &t1, const Time &t2) const;


  void sortById() {
    sorting::radix_sort(dataList.begin(), dataList.end(),
                  std::function<unsigned (Message &m)>
                    ([](Message &m) -> uint16_t {return m.senderID;}));
  }

  void sortByType() {
    sorting::counting_sort(dataList.begin(), dataList.end(), 0, 6,
                 std::function<unsigned (Message &m)>
                   ([](Message &m) -> uint16_t {return uint16_t(m.type);}));
  }

  void std_stable_sortById () {
    std::stable_sort(dataList.begin(), dataList.end(),
                   [](Message a, Message b) {return a.senderID < b.senderID; });
  }

  void std_stable_sortByType () {
    std::stable_sort(dataList.begin(), dataList.end(),
                     [](Message a, Message b) {return a.type < b.type; });
  }

};