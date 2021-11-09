#pragma once

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <string>
#include <variant>

#include <unistd.h>
#include <wait.h>

#include <SFML/Window.hpp>
#include <boost/process.hpp>

#include "ClientServer.hpp"
#include "Functions.hpp"
#include "Config.hpp"

namespace bp = boost::process;
namespace cf = os::lab1::compfuncs;

template<typename T>
class Manager {
  using Result = cf::comp_result<T>;

  void keyHandler();
  void killProcesses();
  static Result binaryOperation(Result a, Result b);
  void monitorFunc(T x, std::promise<Result> &promise,
                   std::unique_ptr<Server> &server,
                   const std::string &displayedName);

public:
  [[noreturn]] explicit Manager(std::string path);

private:
  std::unique_ptr<bp::child> childF;
  std::unique_ptr<bp::child> childG;
  std::unique_ptr<Server> serverF;
  std::unique_ptr<Server> serverG;
  std::mutex iomutex;

  bool computing = false;
  bool stopped = false;
};


template<typename T>
Manager<T>::Manager(std::string path) {
  new std::thread([this](){this->keyHandler();});

  while (!stopped) {
    nested_continue:
    serverF.reset();
    serverG.reset();

    serverF = std::make_unique<Server>(Config::PortF);
    serverG = std::make_unique<Server>(Config::PortG);

    childF = std::make_unique<bp::child>(path, "-f");
    childG = std::make_unique<bp::child>(path, "-g");

    while (!stopped) {
      std::cout << "\nInput x:" << std::endl;

      T x;
      std::cin >> x;

      std::promise<Result> promiseF;
      std::promise<Result> promiseG;

      computing = true;
      new std::thread([&](){this->monitorFunc(x, promiseF, serverF, "f(x)");});
      new std::thread([&](){this->monitorFunc(x, promiseG, serverG, "g(x)");});

      auto resF = promiseF.get_future().get();
      auto resG = promiseG.get_future().get();
      computing = false;

      if (std::holds_alternative<cf::soft_fail>(resF) ||
          std::holds_alternative<cf::soft_fail>(resF)) {
        // it's kinda ok to use goto for breaking or continuing in nested loop
        goto nested_continue;
      }

      iomutex.lock();
      std::cout << "\nf(" << x << ") = " << resF << std::endl;
      std::cout << "g(" << x << ") = " << resG << std::endl;

      std::cout << "f(" << x << ") * g(" << x << ") = "
                << binaryOperation(resF, resG) << std::endl;

      iomutex.unlock();
    }
  }
}


template<typename T>
void Manager<T>::keyHandler() {
  bool isContinued = false;
  while (!stopped) {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::C)
        && computing) || isContinued) {

      if (!isContinued)
        iomutex.lock();

      isContinued = false;

      std::cout << "Please confirm that computation should be stopped y(es, stop)/n(ot yet) [n]" << std::endl;

      struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };
      std::string str;

      int ret = poll(&pfd, 1, 10000);

      if (ret == 1) {
        std::cin >> str;
        if (str == "y" || str == "yes" || str == "stop") {
          killProcesses();
        }
        else if (str == "n" || str == "not" || str == "yet") {
          std::cout << "Proceeding...\n\n";
        }
        else {
          isContinued = true;
          continue;
        }
      }
      else {
        std::cout << "Action is not confirmed within 10 seconds. Proceeding..." << std::endl;
      }
      iomutex.unlock();
    }
  }
}


template<typename T>
typename Manager<T>::Result Manager<T>::
    binaryOperation(Result a, Result b) {

  if (std::holds_alternative<cf::hard_fail>(a) ||
      std::holds_alternative<cf::hard_fail>(b)) {
    return cf::hard_fail();
  }
  else {
    auto av = std::get<T>(a);
    auto bv = std::get<T>(b);
    return (av + bv) + av * bv;
  }
}


template<typename T>
void Manager<T>::monitorFunc(T x, std::promise<Result> &promise,
                             std::unique_ptr<Server> &server,
                             const std::string &displayedName) {
  Result res;

  try {
    server->write(x);
    res = server->read<Result>();
  }
  catch (std::exception &e) {
    std::cout << displayedName << " computation canceled" << std::endl;
    promise.set_value(cf::soft_fail());
    return;
  }

  iomutex.lock();
  std::cout << displayedName << " computation completed ("
            << res << ")" << std::endl;
  iomutex.unlock();

  promise.set_value(res);
}

template<typename T>
void Manager<T>::killProcesses() {
  kill(childF->id(), SIGKILL);
  kill(childG->id(), SIGKILL);
  int status;
  waitpid(childF->id(), &status, 0);
  waitpid(childG->id(), &status, 0);
}
