#pragma once

#include <string>
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
  void saveToTextFile(std::ofstream &out)
  {
    out << senderLogin << ' ' << receiverLogin << std::endl;
    out << time.sec << ' ' << time.min << ' ' <<
          time.hour << ' ' << time.day << ' ' <<
          time.month << ' ' << time.month;

    out << spamProbability << std::endl;
    out << text << std::endl;
  }

  void loadFromTextFile(std::ifstream &in)
  {
    in >> senderLogin >> receiverLogin;
    in >> time.sec >> time.min >>
        time.hour >> time.day >>
        time.month >> time.month;

    in >> spamProbability;
    std::getline(in, text);
  }

  void saveToBinFile(std::ofstream &out)
  {

  }


};