#pragma once

#include <iostream>
#include "Vector3.h"
#include "exceptions.hpp"

class Ray {
private:
    Vector3 origin;
    Vector3 end;
    int samples;

public:
    Ray();
    Ray(const Vector3 &_origin, const Vector3 &_end, const int &_samples);
    Ray(const Ray &other);
    Ray & operator=(const Ray &other);
    ~Ray();

    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

    Vector3 RayCast(int k);
};
