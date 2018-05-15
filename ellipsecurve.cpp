#include "ellipsecurve.hpp"

using namespace std;

TDouble ECURVE_A = -7;
TDouble ECURVE_B = 10;

/*EllipseCurve::EllipseCurve(void) {
	this->SetParams(1, 1);
}
EllipseCurve::EllipseCurve(TDouble a, TDouble b) {
	this->SetParams(a, b);
}
void EllipseCurve::SetParams(TDouble a, TDouble b) {
	if (4*a*a*a + 27*b*b == 0) {
		a = 1;
		b = 1;
	}
	this->A = a;
	this->B = b;
}*/

EPoint::EPoint(void) {
	this->SetInf();
}
EPoint::EPoint(TDouble x, TDouble y) {
	this->X = x;
	this->Y = y;
}

bool EPoint::IsInf(void) {
	return this->X == INF || this->Y == INF;
}
void EPoint::SetInf(void) {
	this->X = INF;
	this->Y = INF;
}

EPoint operator -(const EPoint &pnt) {
	return EPoint(pnt.X, -pnt.Y);
}

std::ostream& operator <<(std::ostream &os, const EPoint &pnt){
        os << "(" << pnt.X << ", " << pnt.Y << ")";
        return os;
    }
const bool operator ==(const EPoint &pnt1, const EPoint &pnt2) {
	return pnt1.X == pnt2.X && pnt1.Y == pnt2.Y;
}
const bool operator !=(const EPoint &pnt1, const EPoint &pnt2) {
	return !(pnt1 == pnt2);
}
EPoint operator +(const EPoint &pnt1, const EPoint &pnt2) {
	if (pnt1 == -pnt2) {
		return EPoint();
	}
	if (pnt1.X == INF || pnt1.Y == INF) {
		return pnt2;
	}
	if (pnt2.X == INF || pnt2.Y == INF) {
		return pnt1;
	}

	TDouble m = 1.;
	if (pnt1 != pnt2) {
		m = (pnt1.Y - pnt2.Y) / (pnt1.X - pnt2.X);
	} else {
		m = (3 * pnt1.X*pnt1.X + ECURVE_A) / (2 * pnt1.Y);
	}
	TDouble xn = m*m - pnt1.X - pnt2.X;
	TDouble yn = pnt1.Y + m * (xn - pnt1.X);
	return EPoint(xn, -yn);
}
EPoint operator -(const EPoint &pnt1, const EPoint &pnt2) {
	return pnt1 + (-pnt2);
}
EPoint operator *(const size_t &num, const EPoint &pnt) {
	if (num == 0) {
		return EPoint(INF, INF);
	}
	if (num == 1) {
		return pnt;
	}
	size_t mid = num / 2;
	return pnt * mid + pnt * (num - mid);
}
EPoint operator *(const EPoint &pnt, const size_t &num) {
	return num * pnt;
}
