#ifndef ELLIPSECURVE_HPP
#define ELLIPSECURVE_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <string>

typedef long double TDouble;

const long long INF = std::numeric_limits<long long>::max();

/*class EllipseCurve {
private:
	long long A;
	long long B;

public:
	EllipseCurve(void);
	EllipseCurve(long long a, long long b);

	void SetParams(long long a, long long b);
};*/

class EPoint {
public:
	long long X;
	long long Y;

	EPoint(void);
	EPoint(long long x, long long y);
	EPoint(EPoint *sample);

	bool IsInf(void);
	void SetInf(void);

	friend EPoint operator -(const EPoint &pnt);
	friend std::ostream& operator<<(std::ostream& os, const EPoint& pnt);
};

//std::ostream& operator<<(std::ostream& os, const EPoint& pnt);
const bool operator ==(const EPoint &pnt1, const EPoint &pnt2);
const bool operator !=(const EPoint &pnt1, const EPoint &pnt2);
EPoint operator +(const EPoint &pnt1, const EPoint &pnt2);
EPoint operator -(const EPoint &pnt1, const EPoint &pnt2);
EPoint operator *(const long long &num, const EPoint &pnt);
EPoint operator *(const EPoint &pnt, const long long &num);
EPoint operator /(const EPoint &pnt1, const EPoint &pnt2);
EPoint operator %(const EPoint &pnt, const long long &p);

#endif //ELLIPSECURVE_HPP
