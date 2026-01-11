#include "interval.h"

double interval::size() const {
  return max - min;
}
bool interval::contains(double x) const {
  return x >= min && x <= max;
}
bool interval::surrounds(double x) const {
  return x > min && x < max;
}