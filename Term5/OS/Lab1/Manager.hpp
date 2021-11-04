#pragma once

#include <iostream>
#include <thread>
#include <future>

#include <boost/process.hpp>
#include <string>

#include "ClientServer.hpp"
#include "Functions.hpp"
#include "Config.hpp"

namespace bp = boost::process;
namespace cf = os::lab1::compfuncs;

template<typename T>
void monitorFunc(T x, std::promise<cf::comp_result<T>> &promise, Server &server, const std::string &displayedName) {
  server.write(x);

  auto res = server.read<cf::comp_result<T>>();
  std::cout << displayedName << " computation completed (" << res << ")" << std::endl;
  promise.set_value(res);
}

template<typename T>
static cf::comp_result<T> binaryOperation(
    cf::comp_result<T> a, cf::comp_result<T> b) {
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
[[noreturn]] void runManager(std::string path) {
  bp::spawn(path, "-f");
  bp::spawn(path, "-g");

  Server serverF(Config::PortF);
  Server serverG(Config::PortG);

  for (;;) {
    std::cout << "Input x:" << std::endl;

    T x;
    std::cin >> x;

    std::promise<cf::comp_result<T>> promiseF;
    std::promise<cf::comp_result<T>> promiseG;

    new std::thread([&](){monitorFunc(x, promiseF, serverF, "f(x)");});
    new std::thread([&](){monitorFunc(x, promiseG, serverG, "g(x)");});

    auto resF = promiseF.get_future().get();
    auto resG = promiseG.get_future().get();

    std::cout << "\nf(x) = " << resF << std::endl;
    std::cout << "g(x) = " << resG << std::endl;

    std::cout << "f(x) * g(x) = " << binaryOperation(resF, resG) << "\n\n";
  }
}