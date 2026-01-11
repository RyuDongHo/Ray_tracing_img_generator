#ifndef INTERVAL_H
#define INTERVAL_H
#include "math.h"

class interval
{
public:
  double min;
  double max;

  interval() : min(+INF), max(-INF) {}
  interval(double a, double b) : min(a), max(b) {}

  double size() const;
  bool contains(double x) const;
  bool surrounds(double x) const;
  static const interval empty, universe;
};

const interval interval::empty = interval(+INF, -INF);
const interval interval::universe = interval(-INF, +INF);

#endif