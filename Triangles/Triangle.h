#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.hpp"
#include "Vector.hpp"
#include <vector>


class Triangle3D {
public:
	using PointType = float;
	using Point = Point3D<PointType>;
	using Vector = Vector3D<PointType>;
	using Line = Line3D<PointType>;
	using Segment = Segment3D<PointType>;

	Triangle3D(Point p1, Point p2, Point p3): p1_(p1), p2_(p2), p3_(p3),
			s1_(p1, p2), s2_(p2, p3), s3_(p3, p1), n_(p1) {
		Vector a(p1_, p2_);
		Vector b(p1_, p3_);
		n_ = a.vectorMul(b);
		n_.divideBy(n_.abs());
	}

	void intersect(std::vector<Triangle3D*> &set);
	bool intersect(Triangle3D *tr);


	void setIntersected() { intersected_ = true; }
	bool isIntersected() { return intersected_; }

	void print() {
		std::cout << "Triangle: ";
		p1_.print();
		std::cout << ", ";
		p2_.print();
		std::cout << ", ";
		p3_.print();
		std::cout << "\n";
	}

private:
	Vector getNormal();
	PointType getD();
	bool arePlanesParallel(Triangle3D &tr2);
	Line getPlanesIntersection(Triangle3D& tr2);

	bool isIntersectOnPlane(Triangle3D *tr2);
	bool isIntersectBetweenPlanes(Triangle3D *tr2);

	PointType getDistanceToPoint(Point p);
	Point getIntersectionByLine(Line &l); // not parallel

	bool haveSegment(Line &l);
	Segment getLineSegment(Line &l);

	bool isContainPoint(Point p);

	Point p1_, p2_, p3_;
	Segment s1_, s2_, s3_;
	Vector n_;
	bool intersected_ = false;
};

#endif // TRIANGLE_H