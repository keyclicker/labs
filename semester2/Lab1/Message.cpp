#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "Message.hpp"

void Message::saveToTextFile(std::ofstream &out) const {
  out << senderLogin << ' ' << receiverLogin << std::endl;
  out << time.hour << ' ' << time.min << ' ' <<
      time.sec << ' ' << time.day << ' ' <<
      time.month << ' ' << time.year << std::endl;

  out << spamProbability << std::endl;
  out << typetos(type) << std::endl;
  out << text << std::endl;
  out << std::endl;
}

void Message::loadFromTextFile(std::ifstream &in) {
  in >> senderLogin >> receiverLogin;
  in >> time.hour >> time.min >>
     time.sec >> time.day >>
     time.month >> time.year;

  in >> spamProbability;

  std::string strType;
  in >> strType;
  type = stotype(strType);

  in.get();

  std::getline(in, text);
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
}

void Message::print() const {
  std::cout << senderLogin << ' ' << receiverLogin << std::endl;
  std::cout << time.hour << ' ' << time.min << ' ' <<
            time.sec << ' ' << time.day << ' ' <<
            time.month << ' ' << time.year << std::endl;

  std::cout << spamProbability << std::endl;
  std::cout << typetos(type) << std::endl;
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
      "anim", "id", "est", "laborum", "dolboeb", "blad", "suka", "blya", "ueban"
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

  return msg;
}

std::string Message::typetos(Message::Type val) const {
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
  };
}

Message::Type Message::stotype(const std::string &val) const {
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

  throw std::logic_error("String cannot be converted to Message::Type");
}
