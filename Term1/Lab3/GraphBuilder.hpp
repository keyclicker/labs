#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>
#include <functional>
#include <vector>

class GraphBuilder
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
  GraphBuilder() = delete;
  GraphBuilder(GraphBuilder &) = delete;
  GraphBuilder(size_t w, size_t h) : w(w), h(h) {}

  void addFunc(const Function &f);
  void run();

private:
  void draw(const Function &f);
};