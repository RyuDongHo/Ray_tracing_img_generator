#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "utils/vec3.h"
#include "utils/interval.h"

class sphere : public hittable {
  public:
    sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0,radius)), mat(mat) {}
    bool hit(const ray& r, const interval& ray_t, hit_record& rec) const;

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif