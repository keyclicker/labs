#pragma once

#include <chrono>
#include <random>
#include "supplementary/compfuncs.hpp"
#include "supplementary/trialfuncs.hpp"

using namespace std::chrono_literals;
namespace cf = os::lab1::compfuncs;

template<typename T>
cf::comp_result<T> trialFunc(T x) {
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<> rDuration(5000, 15000);
  std::uniform_int_distribution<> rAction(0, 4);
  std::uniform_int_distribution<T> rValue(0, 50);

  std::this_thread::sleep_for(std::chrono::milliseconds(rDuration(mt)));
  cf::comp_result<T> res;

  auto a = rAction(mt);
  if (a < 3)
    return rValue(mt);
  else if (a == 3)
    return cf::soft_fail();
  else if (a == 4)
    return cf::hard_fail();
}
