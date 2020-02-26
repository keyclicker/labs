#include "Message.hpp"

void Message::saveToTextFile(std::ofstream &out) const {
  out << senderLogin << ' ' << receiverLogin << std::endl;
  out << time.hour << ' ' << time.min << ' ' <<
      time.sec << ' ' << time.day << ' ' <<
      time.month << ' ' << time.year << std::endl;

  out << spamProbability << std::endl;
  out << text << std::endl;
  out << std::endl;
}

void Message::loadFromTextFile(std::ifstream &in) {
  in >> senderLogin >> receiverLogin;
  in >> time.hour >> time.min >>
     time.sec >> time.day >>
     time.month >> time.year;

  in >> spamProbability;
  in.get();

  std::getline(in, text);
}

void Message::saveToBinFile(std::ofstream &out) const {
  out.write((char *) &time, sizeof(time));
  out.write((char *) &spamProbability, sizeof(spamProbability));

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

  u_int16_t len;
  char *tmpstr;

  in.read((char *) &len, sizeof(len));
  tmpstr = new char[len];
  in.read(tmpstr, len);
  senderLogin = std::string(tmpstr);

  in.read((char *) &len, sizeof(len));
  tmpstr = new char[len];
  in.read(tmpstr, len);
  receiverLogin = std::string(tmpstr);

  in.read((char *) &len, sizeof(len));
  tmpstr = new char[len];
  in.read(tmpstr, len);
  text = std::string(tmpstr);
}

void Message::print() const {
  std::cout << senderLogin << ' ' << receiverLogin << std::endl;
  std::cout << time.hour << ' ' << time.min << ' ' <<
            time.sec << ' ' << time.day << ' ' <<
            time.month << ' ' << time.year << std::endl;

  std::cout << spamProbability << std::endl;
  std::cout << text << std::endl;
  std::cout << std::endl;
}
