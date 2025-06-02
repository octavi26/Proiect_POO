#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"
#include "exceptions.hpp"

class Camera {
private:
    Vector3 position;
    float fov;
    int columns, lines;
    float size;
    int samples;
    float maxDistance;

public:
    Camera();
    Camera(const Vector3 &_position, float _fov, int _lines, float _size, int _columns, float _maxDistance, int _samples);
    Camera(const Camera &other);
    Camera & operator=(const Camera &other);
    ~Camera();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    void SetRatio(int _columns, int _lines);
    void Move(Vector3 transform);
    float Value(int x, int y, const std::vector<std::shared_ptr<Shape>>& shapes, Light light);
};
