#pragma once

#include <boost/asio.hpp>
#include <thread>

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
    socket.write_some(asio::buffer(&value, sizeof(T)));
  }

  template<typename T>
  T read() {
    T value;
    socket.read_some(asio::buffer(&value, sizeof(T)));
    return value;
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

    new std::thread([&](){acceptor.accept(socket);});
  }

  Server() = delete;
  Server(const Server &) = delete;
  Server &operator=(const Server &) = delete;
};