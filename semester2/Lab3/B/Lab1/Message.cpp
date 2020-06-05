#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include "Message.hpp"

void Message::saveToTextFile(std::ofstream &out) const {
  out << senderLogin << ' ' << receiverLogin << std::endl;
  out << int(time.hour) << ' ' << int(time.min) << ' ' <<
      int(time.sec) << ' ' << int(time.day) << ' ' <<
      int(time.month) << ' ' << time.year << std::endl;

  std::cout << std::fixed;
  out << std::setprecision(6) << spamProbability << std::endl;
  out << typetos(type) << std::endl;
  out << text << std::endl;
}

void Message::loadFromTextFile(std::ifstream &in) {
  in >> senderLogin >> receiverLogin;
  in >> time;

  in >> spamProbability;

  std::string strType;
  in >> strType;
  type = stotype(strType);

  in.get();
  std::getline(in, text);

  for (auto a : senderLogin)
    senderID += a;
}

void Message::saveToBinFile(std::ofstream &out) const {
  out.write((char *) &time, sizeof(time));
  out.write((char *) &spamProbability, sizeof(spamProbability));
  out.write((char *) &type, sizeof(type));

  u_int16_t len = senderLogin.length();
  out.write((char *) &len, sizeof(len));
  out.write(senderLogin.data(), len);

  len = receiverLogin.length();
  out.write((char *) &len, sizeof(len));
  out.write(receiverLogin.data(), len);

  len = text.length();
  out.write((char *) &len, sizeof(len));
  out.write(text.data(), len);
}

void Message::loadFromBinFile(std::ifstream &in) {
  in.read((char *) &time, sizeof(time));
  in.read((char *) &spamProbability, sizeof(spamProbability));
  in.read((char *) &type, sizeof(type));

  u_int16_t len;

  in.read((char *) &len, sizeof(len));
  senderLogin.resize(len);
  in.read(senderLogin.data(), len);

  in.read((char *) &len, sizeof(len));
  receiverLogin.resize(len);
  in.read(receiverLogin.data(), len);

  in.read((char *) &len, sizeof(len));
  text.resize(len);
  in.read(text.data(), len);

  for (auto a : senderLogin)
    senderID += a;
}

void Message::print() const {
  std::cout << "SenderID: " << senderID << endl;
  std::cout << senderLogin << " -> " << receiverLogin << std::endl;
  std::cout << int(time.hour) << ':' << int(time.min) << ':' <<
            int(time.sec) << ' ' << int(time.day) << '.' <<
            int(time.month) << '.' << time.year << std::endl;

  std::cout << std::fixed;
  std::cout << "Spam: " << std::setprecision(6) <<spamProbability << std::endl;
  std::cout << "Type: "<< typetos(type) << std::endl;
  std::cout << text << std::endl;
  std::cout << std::endl;
}

std::mt19937 gen(std::time(0));
auto rand(int r1, int r2) {
  std::uniform_int_distribution<int> r(r1, r2);
  return r(gen);
};

Message Message:: Generate() {
  std::mt19937 gen(std::random_device{}());

  static const std::vector<std::string> Names = {
    "Linder1337", "Ivanov42", "Zhereb228", "TheVepesh", "AdzhOBEY"
  };

  static const std::vector<std::string> Words = {
      "lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
      "adipiscing", "elit", "sed", "do", "eiusmod", "tempor", "incididunt",
      "ut", "labore", "et", "dolore", "magna", "aliqua", "ut", "enim", "ad",
      "minim", "veniam", "quis", "nostrud", "exercitation", "ullamco",
      "laboris", "nisi", "ut", "aliquip", "ex", "ea", "commodo", "consequat",
      "duis", "aute", "irure", "dolor", "in", "reprehenderit", "in",
      "voluptate", "velit", "esse", "cillum", "dolore", "eu", "fugiat", "nulla",
      "pariatur", "excepteur", "sint", "occaecat", "cupidatat", "non",
      "proident", "sunt", "in", "culpa", "qui", "officia", "deserunt", "mollit",
      "anim", "id", "est", "laborum"
  };


  Message msg;
  msg.senderLogin = Names[rand(0, 4)];
  msg.receiverLogin = Names[rand(0, 4)];

  msg.time.year = rand(1977, 2020);
  msg.time.month = rand(1, 12);
  msg.time.day = rand(1, 30);
  msg.time.hour = rand(0, 23);
  msg.time.min = rand(0, 59);
  msg.time.sec = rand(0, 59);

  std::uniform_real_distribution<double> realRand(0, 1);
  msg.spamProbability = realRand(gen);

  msg.type = Type(rand(0, 5));

  for (int i = 0; i < rand(1, 25); ++i) {
    msg.text.append(Words[rand(0, Words.size()-1)] + " ");
  }

  msg.senderID = 0;
  for (auto a : msg.senderLogin)
    msg.senderID += a;

  return msg;
}

std::string Message::typetos(Message::Type val) {
  switch (val) {
    case Type::news:
      return "news";
    case Type::question:
      return "question";
    case Type::answer:
      return "answer";
    case Type::invite:
      return "invite";
    case Type::commentOnEvent:
      return "commentOnEvent";
    case Type::commentOnMessage:
      return "commentOnMessage";
    case Type::none:
      return "none";
  };
}

Message::Type Message::stotype(const std::string &val) {
  if (val == "news")
      return Type::news;
  if (val == "question")
      return Type::question;
  if (val == "answer")
      return Type::answer;
  if (val == "invite")
      return Type::invite;
  if (val == "commentOnEvent")
      return Type::commentOnEvent;
  if (val == "commentOnMessage")
      return Type::commentOnMessage;

  return Type::none;
}

Database<Message> Database<Message>::ofSender(const std::string &sender) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.senderLogin == sender)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::inSpamRange(double r1, double r2) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.spamProbability > r1 && a.spamProbability < r2)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::ofType(Message::Type type) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.type == type)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::contains(const std::string &text) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.text.find(text) != std::string::npos)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::sentAfter(const Time &time) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.time > time)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::sentBefore(const Time &time) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.time < time)
      subdb.push(a);
  }
  return subdb;
}

Database<Message> Database<Message>::Generate(size_t size) {
  Database<Message> db;
  for (size_t i = 0; i < size; ++i) {
    db.push(Message::Generate());
  }
  return db;
}

Database<Message>
Database<Message>::ofReceiver(const std::string &receiver) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.receiverLogin == receiver)
      subdb.push(a);
  }
  return subdb;
}

Database<Message>
Database<Message>::inTimeRange(const Time &t1, const Time &t2) const {
  Database<Message> subdb;
  for (auto &a : getData()) {
    if (a.time > t1 && a.time < t2)
      subdb.push(a);
  }
  return subdb;

}

void Message::printCompact() const {
  std::cout << std::setw(11) << senderID;

  switch (type) {
    case Type::answer: std::cout            << "   answer           "; break;
    case Type::commentOnEvent: std::cout    << "   commentOnEvent   "; break;
    case Type::commentOnMessage: std::cout  << "   commentOnMessage "; break;
    case Type::invite: std::cout            << "   invite           "; break;
    case Type::news: std::cout              << "   news             "; break;
    case Type::question: std::cout          << "   question         "; break;
    case Type::none: std::cout              << "   none             "; break;
  }
}
