#include "utils/interval.h"

const interval interval::empty = interval(+INF, -INF);
const interval interval::universe = interval(-INF, +INF);

double interval::size() const {
  return max - min;
}
bool interval::contains(double x) const {
  return x >= min && x <= max;
}
bool interval::surrounds(double x) const {
  return x > min && x < max;
}
double interval::clamp(double x) const {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}