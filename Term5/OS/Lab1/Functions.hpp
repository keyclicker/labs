#pragma once

#include <chrono>

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

    auto res = func(x);
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