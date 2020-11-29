#include "Point.hpp"
#include "Vector.hpp"
#include "Triangle.h"
#include <iostream>
#include <cstring>
#include <vector>


Triangle3D::Point pointFromInput() {
	Triangle3D::PointType x, y, z;
	std::cin >> x;
	std::cin >> y;
	std::cin >> z;
	return Triangle3D::Point(x, y, z);
}

Triangle3D *triangleFromInput() {
	Triangle3D::Point p1 = pointFromInput();
	Triangle3D::Point p2 = pointFromInput();
	Triangle3D::Point p3 = pointFromInput();
	if (p1.isCollinear(p2, p3)) {
		std::cout << "Maaan dat triagnle totaly suuux\n";
		return nullptr;
	}
	return new Triangle3D(p1, p2, p3);
}

int main(int argc, char* argv[]) {
	if (argc > 1 && !strcmp(argv[1], "test")) {
		std::cout << "tests:\n";
		//runTests();
	}
	else if (argc > 2 && !strcmp(argv[1], "file")) {
		std::cout << "Run from file: " << argv[2] << "\n";
		//runFromFile(argc[2]);
	}
	else
	{
		int N;
		std::cin >> N;
		if (N > 1 && N < 1000000) {
			std::vector<Triangle3D*> triangles;
			for (int i = 0; i < N; i++) {
				Triangle3D *tr = triangleFromInput();
				if (!tr) {
					return 1;
				}
				tr->intersect(triangles);
				tr->print();
				triangles.push_back(tr);
			}

			for (int i = 0; i < N; i++) {
				if (triangles[i]->isIntersected())
					std::cout << i << " ";
			}
		}
	}

	return 0;
}