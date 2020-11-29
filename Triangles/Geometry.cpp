#include "Point.hpp"
#include "Vector.hpp"
#include "Triangle.h"

using Point = Point3D<Triangle3D::PointType>;
using Vector = Vector3D<Triangle3D::PointType>;

bool Point::isCollinear(Point p2, Point p3) {
	Vector a(*this, p2);
	Vector b(*this, p3);
	return a.vectorMul(b).abs() == 0;
}
