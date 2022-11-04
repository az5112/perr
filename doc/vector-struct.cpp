#include <vector>
#include "perr.h"

struct Rectangle {
	int height;
	int width;
};

std::ostream& operator<< (std::ostream& os, Rectangle const& r) {
	os << "{" << r.height << "x" << r.width << "}";
	return os;
};

int main() {
	std::vector< Rectangle > vr = { {2, 3}, {4, 5} };
	perr << vr;
}
