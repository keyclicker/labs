#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "Time.hpp"

class Message {
public:
  enum class Type {
    news, question, answer, invite, commentOnEvent, commentOnMessage
  };

  void loadFromTextFile(std::ifstream &in);
  void saveToTextFile(std::ofstream &out) const;

  void loadFromBinFile(std::ifstream &in);
  void saveToBinFile(std::ofstream &out) const;

  void print() const;

  static Message Generate();

private:
  std::string senderLogin;
  std::string receiverLogin;
  std::string text;
  Time time;
  double spamProbability;
  Type type;

  std::string typetos(Type val) const;
  Type stotype(const std::string &val) const;
};