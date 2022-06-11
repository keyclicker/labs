#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;

#include "Utils.hpp"

// Node
class RangeTree {
private:
  Range<> range;
  shared_ptr<vector<Point>> points; // all points sorted by x
  unique_ptr<RangeTree> left, right;
  vector<Point> segPoints; // segment sorted by y

public:
  RangeTree(Range<> range, RangeTree *left = nullptr, RangeTree *right = nullptr):
  range(range), left(left), right(right) {}


  // points - sorted by x
  RangeTree(shared_ptr<vector<Point>> sortedPoints, Range<> range):
  range(range), points(move(sortedPoints)), left(nullptr), right(nullptr), 
  segPoints(range.max - range.min) {

    if (range.max - range.min <= 1) {
      segPoints[0] = (*points)[range.min];
      return;
    }

    for (int i = range.min; i < range.max; i++) {
      segPoints[i - range.min] = (*points)[i];
    }

    sort(segPoints.begin(), segPoints.end(),
    [](const Point &a, const Point &b) {
      return a.y < b.y;
    });

    int mid = (range.min + range.max) / 2;
    left = make_unique<RangeTree>(points, Range<>(range.min, mid));
    right = make_unique<RangeTree>(points, Range<>(mid, range.max));
  }

  static RangeTree *buildRangeTree(const vector<Point> &points) {
    auto sPoints = make_shared<vector<Point>>(points);
    sort(sPoints->begin(), sPoints->end(),
    [](const Point &a, const Point &b) {
      return a.x < b.x;
    });

    return new RangeTree(sPoints, {0, points.size()});
  }

  // normalizes x range and runs search
  list<Point> search(Range<double> x, Range<double> y) {
    Range<size_t> normX;

    auto comp = [](const Point &a, double b) {
      return a.x < b;
    };

    normX.min = lower_bound(points->begin(),
    points->end(), x.min, comp) - points->begin();

    normX.max = lower_bound(points->begin(),
    points->end(), x.max, comp) - points->begin();

    cout << "Normal Range: " << normX
    << ' ' << y << "\n\nSearching\n";

    return searchX(normX, y);
  }

  // x - normalized x range
  list<Point> searchX(Range<size_t> x, Range<double> y) {
    if (x.min <= range.min && range.max <= x.max) {
      auto results = searchY(y);
      cout << "X range - " << x << ":\n" << results << endl;
      return results;
    }

    auto mid = (range.min + range.max) / 2;
    list<Point> leftPoints;
    list<Point> rightPoints;

    if (left && x.min < mid)
      leftPoints = left->searchX(Range(x.min, mid), y);
    if (right && mid < x.max)
      rightPoints = right->searchX(Range(mid, x.max), y);

    leftPoints.insert(leftPoints.end(), rightPoints.begin(), rightPoints.end());
    return leftPoints;
  }

  list<Point> searchY(Range<double> y) {
    list<Point> results;

    auto start = lower_bound(segPoints.begin(), segPoints.end(), y.min,
    [](const Point &a, double b) {
      return a.y < b;
    });

    for (auto i = start; i != segPoints.end() && i->y <= y.max; i++) {
      results.push_back(*i);
    }

    return results;
  }
};