#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

template <class type>
class Point3D {
public: 
	Point3D(type x, type y, type z) : x_(x), y_(y), z_(z) {}

	type getX() { return x_; }
	type getY() { return y_; }
	type getZ() { return z_; }

	void print() const {
		std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")";
	}

	bool isCollinear(Point3D<type> p2, Point3D<type> p3);
	static bool isCollinear(Point3D<type>& p1, Point3D<type>& p2, Point3D<type>& p3) {
		return p1.isCollinear(p2, p3);
	}

	bool isEqual(Point3D<type> p2) const {
		return (x_ == p2.x_) && (y_ == p2.y_) && (z_ == p2.z_);
	}

private:
	type x_, y_, z_;
};


#endif // POINT_HPP
