#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ellipsecurve.hpp"

using namespace std;

int main(void) {
	EPoint p(1, 2);
	EPoint q(1, 2);
	cout << p + p + p  << endl;
	cout << 3 * p << endl;

	return 0;
}

