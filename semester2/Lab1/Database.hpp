#pragma once

#include <list>
#include <string>
#include <fstream>
#include "Message.hpp"

template <typename T = Message>
class Database
{
private:
  std::list<Message> messageList; //todo Message to T

public:
  void saveToTextFile(const std::string &path) const
  {
    std::ofstream out(path, std::ios::out);
    for (auto &a : messageList)
      a.saveToTextFile(out);
  }

  void loadToTextFile(const std::string &path) const
  {
    std::ifstream in(path, std::ios::in);
    for (auto &a : messageList)
      a.loadFromTextFile(in);
  }

  void saveToBinFile(const std::string &path) const
  {
    std::ofstream out(path, std::ios::out | std::ios::binary);

  }

};
