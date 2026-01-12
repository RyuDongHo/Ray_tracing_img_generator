#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "utils/ray.h"
#include "utils/vec3.h"
#include <memory>

class material;

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    std::shared_ptr<material> mat;
    /*
    충돌지점에서 ray의 시작점이 물체 외부인 경우
    법선 벡터가 바깥쪽을 향하도록 설정
    물체 내부인 경우
    법선 벡터가 안쪽을 향하도록 설정
    */
    void set_face_normal(const ray& r, const vec3& outward_normal){
      front_face = dot(r.direction(), outward_normal) < 0;
      normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif
