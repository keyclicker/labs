#pragma once

#include <chrono>
#include <variant>

#include "ClientServer.hpp"
#include "Config.hpp"
#include "TrialFunc.hpp"

#include "supplementary/compfuncs.hpp"
#include "supplementary/trialfuncs.hpp"

namespace cf = os::lab1::compfuncs;

template<typename T,typename F>
[[noreturn]] void runFunction(F func, uint16_t port) {
  Client client(port);
  for (;;) {
    T x = client.read<T>();

    cf::comp_result<T> res;

    int attempt = 0;
    do {
      res = func(x);
    } while (std::holds_alternative<cf::soft_fail>(res)
      && attempt < Config::MaxAttemptsCount);

    if (std::holds_alternative<cf::soft_fail>(res))
      client.write(cf::hard_fail());
    else
      client.write(res);
  }
}

template<typename T>
void functionF() {
  runFunction<T>(trialFunc<T>, Config::PortF);
}

template<typename T>
void functionG() {
  runFunction<T>(trialFunc<T>, Config::PortG);
}

//cf::trial_g<cf::INT_SUM>