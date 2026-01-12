#ifndef CAMERA_H
#define CAMERA_H

#include "hittables/hittable.h"
#include "utils/color.h"
#include "utils/vec3.h"

class camera
{
public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;
  void render(const hittable &world);
  int max_depth = 30;
  double vfov = 90.0;
private:
  int image_height;   // Rendered image height
  point3 camera_center;      // Camera center
  point3 pixel00_loc; // Location of pixel 0, 0
  vec3 pixel_delta_u; // Offset to pixel to the right
  vec3 pixel_delta_v; // Offset to pixel below
  double pixel_samples_scale;


  void initialize();
  color ray_color(const ray &r, int depth, const hittable &world);
  ray get_ray(int i, int j) const;
  vec3 sample_square() const;
};

#endif