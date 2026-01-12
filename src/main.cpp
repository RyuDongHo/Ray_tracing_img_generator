#include <iostream>
#include "utils/color.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/math.h"
#include "hittables/hittable.h"
#include "hittables/hittableList.h"
#include "hittables/sphere.h"
#include "utils/camera.h"
#include "material/lambertian.h"
#include "material/metal.h"

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

int main()
{
  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}