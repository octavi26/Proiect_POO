#pragma once
#include "Shape.h"

class Torus : public Shape {
private:
    float thickness;

protected:
    void afisare(std::ostream& os) const override;

public:
    Torus();
    Torus(const Vector3 &_position, const Vector3 &_scale, const Vector3 &_rotation, const float &_thickness);
    Torus(const Torus &other);
    Torus& operator=(const Torus &other);

    float getThickness() const;

    std::shared_ptr<Shape> clone() const override;
    bool accept(InsideVisitor& visitor, Vector3 point) const override;
};
