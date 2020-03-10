#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "Time.hpp"
#include "Database.hpp"

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

  static Message Generate();

  std::string senderLogin;
  std::string receiverLogin;
  std::string text;
  Time time;
  double spamProbability;
  Type type;

private:
  std::string typetos(Type val) const;
  Type stotype(const std::string &val) const;
};

using MS = Database<Message>;

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
};