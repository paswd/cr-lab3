#ifndef ELLIPSECURVE_HPP
#define ELLIPSECURVE_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <string>

typedef long double TDouble;

const TDouble INF = std::numeric_limits<TDouble>::max();

/*class EllipseCurve {
private:
	TDouble A;
	TDouble B;

public:
	EllipseCurve(void);
	EllipseCurve(TDouble a, TDouble b);

	void SetParams(TDouble a, TDouble b);
};*/

class EPoint {
public:
	TDouble X;
	TDouble Y;

	EPoint(void);
	EPoint(TDouble x, TDouble y);

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
EPoint operator *(const size_t &num, const EPoint &pnt);
EPoint operator *(const EPoint &pnt, const size_t &num);
EPoint operator /(const EPoint &pnt1, const EPoint &pnt2);

#endif //ELLIPSECURVE_HPP
