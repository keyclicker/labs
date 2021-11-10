#pragma once

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <string>
#include <utility>
#include <variant>
#include <chrono>
#include <condition_variable>

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

  void prompt();
  void reset();
  void killChildren();
  static Result binaryOperation(Result a, Result b);
  void monitorFunc(T x, std::promise<Result> &promise,
                   std::unique_ptr<Server> &server,
                   const std::string &displayedName);

public:
  [[noreturn]] explicit Manager(std::string path);
  void stop();

private:
  std::unique_ptr<bp::child> childF;
  std::unique_ptr<bp::child> childG;
  std::unique_ptr<Server> serverF;
  std::unique_ptr<Server> serverG;

  std::mutex promptLock;

  bool stopped = false;
  bool isCompleted = false; // is computation completed

  std::string path;
};


template<typename T>
Manager<T>::Manager(std::string path): path(std::move(path)){
  reset();
  while (!stopped) {
    std::cout << "Input x:" << std::endl;

    T x;
    std::cin >> x;

    new std::thread([this]() { this->prompt(); });

    std::promise<Result> promiseF;
    std::promise<Result> promiseG;

    new std::thread([&]() { this->monitorFunc(x, promiseF, serverF, "f(x)"); });
    new std::thread([&]() { this->monitorFunc(x, promiseG, serverG, "g(x)"); });

    auto resF = promiseF.get_future().get();
    auto resG = promiseG.get_future().get();

    isCompleted = true;

    //waiting for prompt user response
    std::lock_guard ul(promptLock);

    bool isCanceledF = std::holds_alternative<cf::soft_fail>(resF);
    bool isCanceledG = std::holds_alternative<cf::soft_fail>(resG);

    if (isCanceledF)
      std::cout << "\nf(" << x << ")" << " has been canceled" << std::endl;
    else
      std::cout << "\nf(" << x << ") = " << resF << std::endl;

    if (isCanceledG)
      std::cout << "g(" << x << ")" << " has been canceled" << "\n\n";
    else
      std::cout << "g(" << x << ") = " << resG << "\n\n";

    if (isCanceledF || isCanceledG) {
      reset();
      continue;
    }

    std::cout << "f(" << x << ") * g(" << x << ") = "
              << binaryOperation(resF, resG) << "\n\n";
  }
}


template<typename T>
void Manager<T>::reset() {
  serverF.reset();
  serverG.reset();

  serverF = std::make_unique<Server>(Config::PortF);
  serverG = std::make_unique<Server>(Config::PortG);

  childF = std::make_unique<bp::child>(path, "-f");
  childG = std::make_unique<bp::child>(path, "-g");
}


template<typename T>
void Manager<T>::prompt() {
  isCompleted = false;
  while (!stopped) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (isCompleted) return;

    std::lock_guard ul(promptLock);

    std::cout << "Please, choose an action:\n"
                 "a) continue\n"
                 "b) continue without prompt\n"
                 "c) stop\n"
                 ">> ";

    std::string str;
    std::cin >> str;

    if (str[0] == 'a') {
      if (isCompleted) return;
      else continue;
    } else if (str[0] == 'b') {
      return;
    } else if (str[0] == 'c') {
      if (!isCompleted)
        killChildren();
      return;
    }
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
    res = cf::soft_fail();
  }

  promise.set_value(res);
}


template<typename T>
void Manager<T>::killChildren() {
  kill(childF->id(), SIGKILL);
  kill(childG->id(), SIGKILL);
  int status;
  waitpid(childF->id(), &status, 0);
  waitpid(childG->id(), &status, 0);
}


template<typename T>
typename Manager<T>::Result Manager<T>::
binaryOperation(Result a, Result b) {
  if (std::holds_alternative<cf::hard_fail>(a) ||
      std::holds_alternative<cf::hard_fail>(b)) {
    return cf::hard_fail();
  } else {
    auto av = std::get<T>(a);
    auto bv = std::get<T>(b);
    return av * bv;
  }
}


template<typename T>
void Manager<T>::stop() {
  stopped = true;
}

