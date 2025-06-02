#pragma once
#include "Shape.h"

class Cube : public Shape {
protected:
    void afisare(std::ostream& os) const override;

public:
    Cube();
    Cube(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation);
    Cube(const Cube &other);
    Cube& operator=(const Cube &other);

    std::shared_ptr<Shape> clone() const override;
    bool accept(InsideVisitor& visitor, Vector3 point) const override;
};
