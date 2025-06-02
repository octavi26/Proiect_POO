#pragma once
#include "Shape.h"

class Sphere : public Shape {
protected:
    void afisare(std::ostream& os) const override;

public:
    Sphere();
    Sphere(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation);
    Sphere(const Sphere &other);
    Sphere& operator=(const Sphere &other);

    std::shared_ptr<Shape> clone() const override;
    bool accept(InsideVisitor& visitor, Vector3 point) const override;
};
