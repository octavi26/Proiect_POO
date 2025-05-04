//
// Created by Octavian on 5/4/2025.
//

#ifndef VECTOR3_H
#define VECTOR3_H

#pragma once

#include <iostream>
#include <cmath>

class Vector3 {
private:
    float x;
    float y;
    float z;
    static constexpr float pi = 3.14159265358979323846f;

public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    Vector3(const Vector3& other);
    Vector3& operator=(const Vector3& other);
    ~Vector3() = default;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& position);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const float& other) const;
    Vector3 operator/(const float& other) const;

    float GetX();
    float GetY();
    float GetZ();
    float Magnitude();
    float CubedMagnitude();

    Vector3 RotateX(float angle);
    Vector3 RotateY(float angle);
    Vector3 RotateZ(float angle);
    Vector3 Rotate(Vector3 rotation);
    Vector3 Scale(Vector3 scale);
    Vector3 Move(Vector3 position);
};


#endif //VECTOR3_H
