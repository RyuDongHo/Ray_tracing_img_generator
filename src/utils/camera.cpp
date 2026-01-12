#include "hittables/hittable.h"
#include "utils/color.h"
#include "utils/camera.h"

ray camera::get_ray(int i, int j) const
{
  // Construct a camera ray originating from the origin and directed at randomly sampled
  // point around the pixel location i, j.

  auto offset = sample_square();
  auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

  auto ray_origin = camera_center;
  auto ray_direction = pixel_sample - ray_origin;

  return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const
{
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void camera::render(const hittable &world)
{
  initialize();
  std::cout << "P3\n"
            << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++)
  {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++)
    {
      color pixel_color(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; ++sample)
      {
        ray r = get_ray(i, j);
        pixel_color += ray_color(r, 0, world);
      }
      write_color(std::cout, pixel_samples_scale * pixel_color);
    }
  }

  std::clog << "\rDone.                 \n";
}
void camera::initialize()
{
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  camera_center = point3(0, 0, 0);

  // Determine viewport dimensions.
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left =
      camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}
color camera::ray_color(const ray &r, int depth, const hittable &world)
{
  if (depth >= max_depth)
    return color(0, 0, 0);
  hit_record rec;
  // 부동 소수점 연산의 오차로 인해, 충돌 지점에서 랜덤한 방향으로 반사될 때
  // 같은 지점에서 반복적으로 충돌 판정을 만드는 것을 방지하기 위해
  // interval의 최소값을 0.001로 설정
  if (world.hit(r, interval(0.001, INF), rec))
  {
    // uniformly sample a random direction
    //vec3 dir = random_on_hemisphere(rec.normal);

    // uniformly sample a random direction = lambertian diffuse
    // reflection ray와 surface normal이 이루는 각이 0일때 가장 밝고 90도일때 0이므로 cos분포를 가진다.
    vec3 dir = rec.normal + random_unit_vector();
    return 0.5 * ray_color(ray(rec.p, dir), depth + 1, world);
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
