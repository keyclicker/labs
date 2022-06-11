#pragma once

#include <iostream>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

class Voronoi {
private:
  typedef pair<double, double> Point;
  #define x first
  #define y second

  struct Arc;
  struct Segment;

  struct Event {
    double x;
    Point p;
    Arc *a;
    bool valid;

    Event(double xx, Point pp, Arc *aa)
        : x(xx), p(pp), a(aa), valid(true) {}
  };

  struct Arc {
    Point p;
    Arc *prev, *next;
    Event *e;

    Segment *s0, *s1;

    Arc(Point pp, Arc *a = 0, Arc *b = 0)
        : p(pp), prev(a), next(b), e(0), s0(0), s1(0) {}
  };

  struct Segment {
    Point start, end;
    bool done;

    Segment(Point p, vector<Segment *> &output)
        : start(p), end(0, 0), done(false) { output.push_back(this); }

    void finish(Point p) {
      if (done) return;
      end = p;
      done = true;
    }
  };

  void processPoint();
  void processEvent();
  void frontInsert(Point p);

  bool circle(Point a, Point b, Point c, double *x, Point *o);
  void checkCircleEvent(Arc *i, double x0);

  bool intersect(Point p, Arc *i, Point *result = 0);
  Point intersection(Point p0, Point p1, double l);

  void finishEdges();

  struct gt {
    bool operator()(Point a, Point b) {
      return a.x == b.x ? a.y > b.y : a.x > b.x;
    }

    bool operator()(Event *a, Event *b) { return a->x > b->x; }
  };

  vector<Segment *> output;
  Arc *root = 0;

  double X0{}, X1{}, Y0{}, Y1{};

  priority_queue<Point, vector<Point>, gt> points;
  priority_queue<Event *, vector<Event *>, gt> events;

public:
  explicit Voronoi(const vector<Point> &p);
  void run();
  void printOutput();
};
