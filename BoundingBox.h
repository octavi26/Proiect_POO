#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Shape.h"
#include "Vector3.h"
#include <memory>

template <typename T>
class BoundingBox : public Shape {
private:
    T shape;
    Vector3 minPoint;
    Vector3 maxPoint;

public:
    BoundingBox(const T& s, const Vector3& minP, const Vector3& maxP);

    std::shared_ptr<Shape> clone() const override;

    bool accept(InsideVisitor& visitor, Vector3 point) const override;
};

#include "BoundingBox.cpp"  // includem .cpp pentru template

#endif // BOUNDINGBOX_H
