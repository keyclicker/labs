#pragma once

#include <boost/asio.hpp>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;


class ClientServerBase {
protected:
  asio::io_context context;
  tcp::socket socket;

public:
  ClientServerBase() : socket(context) {}
  ClientServerBase(const ClientServerBase &) = delete;
  ClientServerBase &operator=(const ClientServerBase &) = delete;

  template<typename T>
  void write(const T &value) {
    try {
      socket.write_some(asio::buffer(&value, sizeof(T)));
    }
    catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  template<typename T>
  T read() {
    try {
      T value;
      socket.read_some(asio::buffer(&value, sizeof(T)));
      return value;
    }
    catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
};

class Client : public ClientServerBase {
  uint16_t port;

public:
  explicit Client(uint16_t port) : port(port) {
    try {
      socket.connect(tcp::endpoint(tcp::v4(), port));
    }
    catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  Client() = delete;
  Client(const Client &) = delete;
  Client &operator=(const Client &) = delete;
};


class Server : public ClientServerBase {
  tcp::acceptor acceptor;

public:
  explicit Server(uint16_t port) : ClientServerBase(),
    acceptor(context, tcp::endpoint(tcp::v4(), port)) {

    acceptor.accept(socket);
  }

  Server() = delete;
  Server(const Server &) = delete;
  Server &operator=(const Server &) = delete;
};