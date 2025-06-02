#ifndef BOUNDINGBOX_CPP
#define BOUNDINGBOX_CPP

#include "BoundingBox.h"

template <typename T>
BoundingBox<T>::BoundingBox(const T& s, const Vector3& minP, const Vector3& maxP)
    : shape(s), minPoint(minP), maxPoint(maxP) {}

template <typename T>
std::shared_ptr<Shape> BoundingBox<T>::clone() const {
    return std::make_shared<BoundingBox<T>>(*this);
}

template <typename T>
bool BoundingBox<T>::accept(InsideVisitor& visitor, Vector3 point) const {
    if (point.GetX() < minPoint.GetX() || point.GetY() < minPoint.GetY() || point.GetZ() < minPoint.GetZ() ||
        point.GetX() > maxPoint.GetX() || point.GetY() > maxPoint.GetY() || point.GetZ() > maxPoint.GetZ()) {
        return false;  // Punctul este în afara bounding box-ului
        }
    return shape.accept(visitor, point);  // Verificăm forma reală
}

#endif // BOUNDINGBOX_CPP
