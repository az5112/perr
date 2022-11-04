#include <vector>
#include "perr.h"

int main() {
	std::vector< int > v = { 1, 2, 3 };
	perr << v;

	v.push_back(44);
	perr << v;

	v.clear();
	perr << v;
};
