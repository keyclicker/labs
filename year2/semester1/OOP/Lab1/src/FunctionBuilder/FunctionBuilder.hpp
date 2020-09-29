#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>
#include <functional>
#include <vector>

class FunctionBuilder
{
private:
  using Function = std::function<double(double)>;

  static constexpr double cMoveSpeed = 1;
  static constexpr double cZoomSpeed = 1.0005;

  size_t w, h;
  double dx = 0, dy = 0;
  double zoom = 1;
  std::vector<Function> functions;

public:
  FunctionBuilder(FunctionBuilder &) = delete;
  FunctionBuilder &operator=(FunctionBuilder &) = delete;

  explicit FunctionBuilder(size_t w = 1280, size_t h = 720) : w(w), h(h) {}
  void run();

  template<typename Func>
  void addFunc(Func &&f) {
    functions.emplace_back(std::forward<Func>(f));
  }

private:
  void draw(const Function &f) const;
};