#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"
#include <cmath>

template <class type>
class Vector3D {
public:
	Vector3D(type x, type y, type z) : x_(x), y_(y), z_(z) {}

	Vector3D(Point3D<type> p1, Point3D<type> p2) {
		x_ = p2.getX() - p1.getX();
		y_ = p2.getY() - p1.getY();
		z_ = p2.getZ() - p1.getZ();
	}

	Vector3D(Point3D<type> p1) {
		x_ = p1.getX();
		y_ = p1.getY();
		z_ = p1.getZ();
	}

	type getX() { return x_; }
	type getY() { return y_; }
	type getZ() { return z_; }

	type scalarMul(Vector3D<type> v2) {
		return x_ * v2.x_ + y_ * v2.y_ + z_ * v2.z_;
	}

	Vector3D<type> vectorMul(Vector3D<type> v2) {
		type x = y_ * v2.z_ - z_ * v2.y_;
		type y = z_ * v2.x_ - x_ * v2.z_;
		type z = x_ * v2.y_ - y_ * v2.x_;
		return Vector3D<type>(x, y, z);
	}

	Vector3D<type> vectorSum(Vector3D<type> v2) {
		type x = x_ + v2.x_;
		type y = y_ + v2.y_;
		type z = z_ + v2.z_;
		return Vector3D<type>(x, y, z);
	}

	bool areParallel(Vector3D<type> v2) {
		return vectorMul(v2).abs() == 0;
	}

	type abs() {
		return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	}

	void divideBy(type div) {
		if (div == 0) {
			std::cout << "Can't divide by zero!\n";
			return;
		}

		x_ /= div;
		y_ /= div;
		z_ /= div;
	}

	void mulBy(type mul) {
		x_ *= mul;
		y_ *= mul;
		z_ *= mul;
	}

	Vector3D<type> negative() {
		return Vector3D<type>(-x_, -y_, -z_);
	}

	Point3D<type> toPoint() {
		return Point3D<type>(x_, y_, z_);
	}

	static type scalarMul(Vector3D<type> v1, Vector3D<type> v2) {
		return v1.scalarMul(v2);
	}

	static Vector3D<type> vectorMul(Vector3D<type> v1, Vector3D<type> v2) {
		return v1.vectorMul(v2);
	}

	static type abs(Vector3D<type> v1) {
		return v1.abs();
	}

	void print() const {
		std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")";
	}

private:
	type x_, y_, z_;
};


template <class type>
class Line3D {
public:
	Line3D(Vector3D<type> v, Point3D<type> p) : v_(v), p_(p) {}

	Vector3D<type> getVector() { return v_; }
	Point3D<type> getPoint() { return p_; }

private:
	Vector3D<type> v_;
	Point3D<type> p_;
};

template <class type>
class Segment3D {
public:
	Segment3D(Point3D<type> p1, Point3D<type> p2) : p1_(p1), p2_(p2), v_(p1, p2) {}

	bool isContainPoint(Point3D<type> p) {
		if (p.isCollinear(p1_, p2_)) {
			Vector3D<type> v1 = (p1_, p);
			type proj = v1.scalarMul(v_);
			if (proj >= 0 && v1.abs() <= v_.abs())
				return true;
		}
		return false;
	}

	Vector3D<type> getVector() { return v_; }

	// assuming not parallel and intersecting
	Point3D<type> getIntersectionPoint(Line3D<type>& l) {
		type t = p1_.getX() - l.getPoint().getX();
		t /= l.getVector().getX() - v_.getX();

		Vector3D<type> v = v_;
		v.mulBy(t);
		return v.vectorSum(Vector3D<type>(p1_)).toPoint();
	}

	bool isIntersectedParallel(Segment3D<type>& s2) {
		return isContainPoint(s2.p1_) || isContainPoint(s2.p2_) ||
				s2.isContainPoint(p1_) || s2.isContainPoint(p2_);
	}

	// assuming not parallel and intersecting
	Point3D<type> getIntersectionPoint(Segment3D<type>& s2) {
		type t = p1_.getX() - s2.p1_.getX();
		t /= s2.v_.getX() - v_.getX();

		Vector3D<type> v = v_;
		v.mulBy(t);
		return v.vectorSum(Vector3D<type>(p1_)).toPoint();
	}

	// assuming on one plane
	bool areIntersecting(Segment3D<type> &s2) {
		Vector3D<type> v1 = v_.vectorMul(Vector3D<type>(p1_, s2.p1_));
		Vector3D<type> v2 = v_.vectorMul(Vector3D<type>(p1_, s2.p2_));

		Vector3D<type> v3 = s2.v_.vectorMul(Vector3D<type>(s2.p1_, p1_));
		Vector3D<type> v4 = s2.v_.vectorMul(Vector3D<type>(s2.p1_, p2_));
		
		type o1 = v1.scalarMul(v2);
		type o2 = v3.scalarMul(v4);

		if (o1 > 0 || o2 > 0) {
			return false;
		}

		if (o1 == 0 && o2 == 0) {
			return isIntersectedParallel(s2);
		}

		return true;

	}

private:
	Vector3D<type> v_;
	Point3D<type> p1_, p2_;

};


#endif // VECTOR_HPP