#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ellipsecurve.hpp"

using namespace std;

int main(void) {
	/*EPoint p(1, 2);
	EPoint q(3, 4);
	cout << p << endl;
	cout << p + p << endl;
	cout << p + q << endl;
	cout << p + p + p  << endl;
	cout << 3 * p << endl;*/

	EPoint bas(1, 3);
	EPoint tmp(&bas);
	size_t cnt = 0;
	do {
		//cout << "MAIN 1" << endl;
		cnt++;
		tmp = tmp + bas;
		//cout << "MAIN 2" << endl;
		//cout << tmp << endl;
		//cout << "MAIN 3" << endl;
	} while (tmp != bas);
	cout << cnt << endl;
	//cout << bas + bas << endl;

	return 0;
}

