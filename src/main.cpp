#include <iostream>
#include "utils/color.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/math.h"
#include "hittables/hittable.h"
#include "hittables/hittableList.h"
#include "hittables/sphere.h"
#include "utils/camera.h"

/*
구체의 중점 center,
카메라의 위치에서 view port로 투영되는 직선을 P(t) = Q + dt 라고 하자 (Q는 카메라 위치, d는 단위 방향 벡터, t는 실수)
이때 직선 P(t)가 구체와 만나는 점 P에 대해서 |P - center| = radius 를 만족한다.
정리하면 (P - C) * (P - C) = r^2 을 만족하고
이를 전개하면 다음과 같은 2차 방정식을 얻는다.
t^2 * (d * d) - 2t * d * (C - Q) + (C - Q)*(C - Q) - r^2 = 0
이때 근의공식에 의해 판별식 D = b^2 - 4ac 가 0 이상이면 직선과 구체가 만난다.
이를 이용하여 ray가 구체와 만나는지 확인하는 hit_sphere 함수를 아래와 같이 작성할 수 있다.

double hit_sphere(const point3 &center, double radius, const ray &r)
{
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
  {
    return -1.0;
  }
  else
  {
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
  }
}

b를 2h로 치환하면
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}
이렇게 변형할 수 있습니다.
*/

color ray_color(const ray &r, const hittable &world)
{
  hit_record rec;
  if (world.hit(r, interval(0, INF), rec))
  {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
  // Image settings
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = static_cast<int>(image_width / aspect_ratio);

  // Objects
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera setup and render
  camera cam;
  cam.aspect_ratio = aspect_ratio;
  cam.image_width = image_width;
  cam.samples_per_pixel = 100;
  cam.render(world);
  
}