#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Time.hpp"

class Message
{
  enum class NewsType
  {
    news, question, answer, invite, commentOnEvent, commentOnMessage
  };

  std::string senderLogin;
  std::string receiverLogin;
  std::string text;
  Time time;
  double spamProbability;

public:
  void loadFromTextFile(std::ifstream &in);
  void saveToTextFile(std::ofstream &out) const;

  void loadFromBinFile(std::ifstream &in);
  void saveToBinFile(std::ofstream &out) const;

  void print() const;
};