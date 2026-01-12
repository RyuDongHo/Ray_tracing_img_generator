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
  point3 lookfrom = point3(0, 0, 0); // Point camera is looking from
  point3 lookat = point3(0, 0, -1);  // Point camera is looking at
  vec3 vup = vec3(0, 1, 0);          // Camera-relative "up" direction
  double defocus_angle = 0;
  double focus_dist = 10;
  

private:
  int image_height;     // Rendered image height
  point3 camera_center; // Camera center
  point3 pixel00_loc;   // Location of pixel 0, 0
  vec3 pixel_delta_u;   // Offset to pixel to the right
  vec3 pixel_delta_v;   // Offset to pixel below
  double pixel_samples_scale;
  vec3 u, v, w; // viewing coordinate axis unit vectors
  vec3 defocus_disk_u;
  vec3 defocus_disk_v;

  void initialize();
  color ray_color(const ray &r, int depth, const hittable &world);
  ray get_ray(int i, int j) const;
  vec3 sample_square() const;
  point3 defocus_disk_sample() const;
};

#endif