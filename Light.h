#pragma once

#include <iostream>
#include "Vector3.h"

class Light {
private:
    Vector3 position;
    float power;

public:
    Light();
    Light(const Vector3 &_position, const float &_power);
    Light(const Light &other);
    Light & operator=(const Light &other);
    ~Light();

    friend std::ostream& operator<<(std::ostream& os, const Light& light);

    float Value(Vector3 point);
    // Vector3 getPosition(); // dacă ai nevoie, decomentează
};
