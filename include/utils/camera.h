#ifndef CAMERA_H
#define CAMERA_H

#include "hittables/hittable.h"
#include "utils/color.h"

class camera
{
public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  void render(const hittable &world);

private:
  int image_height;   // Rendered image height
  point3 camera_center;      // Camera center
  point3 pixel00_loc; // Location of pixel 0, 0
  vec3 pixel_delta_u; // Offset to pixel to the right
  vec3 pixel_delta_v; // Offset to pixel below
  void initialize();
  color ray_color(const ray &r, const hittable &world);
};

#endif