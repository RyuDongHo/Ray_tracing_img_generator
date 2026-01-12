#ifndef HITTABLE_H
#define HITTABLE_H

#include "utils/interval.h"
#include "hitRecord.h"
#include "material/material.h"

class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, const interval& ray_t, hit_record& rec) const = 0;
};

#endif