#include "Triangle.h"
#include "Point.hpp"

void Triangle3D::intersect(std::vector<Triangle3D*> &set) {
	for (auto tr : set) {
		if (intersect(tr)) {
			tr->setIntersected();
			intersected_ = true;
		}
	}
}

bool Triangle3D::intersect(Triangle3D *tr) {
	if (arePlanesParallel(*tr)) {
		if (getDistanceToPoint(tr->p1_) == 0) {
			// triangles on the same plane
			return isIntersectOnPlane(tr);
		} else {
			// planes are parallel but different
			//std::cout << "Nah. Different parallel planes, dude...\n";
			return false;
		}
	} else {
		// planes not parallel
		return isIntersectBetweenPlanes(tr);
	}
}


bool Triangle3D::isIntersectOnPlane(Triangle3D *tr2) {
	//std::cout << "Ohh maaan!! One plane!\n";
	
	Segment ss[3] = { s1_, s2_, s3_ };
	Segment ss2[3] = {tr2->s1_, tr2->s2_, tr2->s3_};
	for (auto s : ss) {
		for (auto s2 : ss) {
			if (s.areIntersecting(s2)) {
				//std::cout << "Daaam! Segments r intersecting! Solid hit, bro!!\n";
				return true;
			}
		}
	}
	// well.. maybe one triangle fully insisde another one?
	return isContainPoint(tr2->p1_) || tr2->isContainPoint(p1_);
}

bool Triangle3D::isIntersectBetweenPlanes(Triangle3D *tr2) {
	//std::cout << "Planes are intersecting!\n";

	Line l = getPlanesIntersection(*tr2);
	if (haveSegment(l) && tr2->haveSegment(l)) {
		Segment s1 = getLineSegment(l);
		Segment s2 = tr2->getLineSegment(l);
		if (s1.isIntersectedParallel(s2)) {
			//std::cout << "This dudes intersect indeeed. Between planes btw -_-\n";
			return true;
		}
	}
	return false;
}

Triangle3D::Vector Triangle3D::getNormal() {
	return n_;
}

Triangle3D::PointType Triangle3D::getD() {
	Vector v(p1_);
	return -v.scalarMul(n_);
}

bool Triangle3D::arePlanesParallel(Triangle3D& tr2) {
	return n_.vectorMul(tr2.getNormal()).abs() == 0;
}

Triangle3D::Line Triangle3D::getPlanesIntersection(Triangle3D& tr2) {
	Vector lv = n_.vectorMul(tr2.getNormal());

	Line l1(lv.vectorMul(n_), p1_);

	return Line(lv, tr2.getIntersectionByLine(l1));
}

Triangle3D::PointType Triangle3D::getDistanceToPoint(Point p) {
	Vector a(p1_, p);
	return a.scalarMul(n_);
}

Triangle3D::Point Triangle3D::getIntersectionByLine(Line& l) {
	Vector pv(l.getPoint());
	Vector v = l.getVector();
	PointType t = - pv.scalarMul(n_);
	t -= getD();
	t /= v.scalarMul(n_);
	v.mulBy(t);
	return v.vectorSum(pv).toPoint();
}


bool Triangle3D::haveSegment(Line& l) {
	Vector v1 = l.getVector().vectorMul(Vector(l.getPoint(), p1_));
	Vector v2 = l.getVector().vectorMul(Vector(l.getPoint(), p2_));
	Vector v3 = l.getVector().vectorMul(Vector(l.getPoint(), p3_));

	PointType o1 = v1.scalarMul(v2);
	PointType o2 = v2.scalarMul(v3);
	PointType o3 = v3.scalarMul(v1);

	if (o1 > 0 && o2 > 0 && o3 > 0)
		return false;
	return true;
}

Triangle3D::Segment Triangle3D::getLineSegment(Line& l) {
	Segment ss[3] = {s1_, s2_, s3_};
	std::vector<Point> ps;
	for (auto s : ss) {
		if (!s.getVector().areParallel(l.getVector())) {
			Point p = s.getIntersectionPoint(l);
			if (s.isContainPoint(p))
				ps.push_back(p);
		}
	}

	if (ps.size() == 2) {
		return Segment(ps[0], ps[1]);
	}

	return Segment(Point(0, 0, 0), Point(0, 0, 0));
}

bool Triangle3D::isContainPoint(Point p) {
	Vector pv1(p1_, p);
	Vector pv2(p2_, p);

	Vector v1 = pv1.vectorMul(s1_.getVector());
	Vector v2 = pv1.vectorMul(s3_.getVector().negative());
	PointType o = v1.scalarMul(v2);

	if (o > 0)
		return false;
	if (o = 0)
		return true;

	v1 = pv2.vectorMul(s2_.getVector());
	v2 = pv2.vectorMul(s1_.getVector().negative());
	o = v1.scalarMul(v2);

	if (o > 0)
		return false;
	return true;
}
