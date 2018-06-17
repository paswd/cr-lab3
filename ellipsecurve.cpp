#include "ellipsecurve.hpp"

using namespace std;

long long	ECURVE_A = 3;
long long	ECURVE_B = 5;
long long	ECURVE_P = 9834497;
//long long	ECURVE_P = 11;

/*EllipseCurve::EllipseCurve(void) {
	this->SetParams(1, 1);
}
EllipseCurve::EllipseCurve(long long a, long long b) {
	this->SetParams(a, b);
}
void EllipseCurve::SetParams(long long a, long long b) {
	if (4*a*a*a + 27*b*b == 0) {
		a = 1;
		b = 1;
	}
	this->A = a;
	this->B = b;
}*/

long long GCDExtended(long long a, long long b, long long &x, long long &y) {
	if (a == 0) {
		x = 0;
		y = 1;
		//cout << "lvl " << lvl << ": IN" << endl;
		//cout << "lvl " << lvl << ": OUT" << endl;
		return b;
	}
	long long x1, y1;
	//cout << "lvl " << lvl << ": IN" << endl;
	long long d = GCDExtended(b % a, a, x1, y1);
	//cout << "lvl " << lvl << ": OUT" << endl;
	x = y1 - (b / a) * x1;
	y = x1;

	return d;
	/*long long s = 0;
	long long old_s;
	long long t = 1;
	long long old_t = 0;
	long long r = b;
	long long old_r = a;

	while (r != 0) {
		long long q = old_r / r;
		long long tmp = old_r;
		old_r = r;
		r = tmp - q * r;

		tmp = old_s;
		old_s = s;
		s = tmp - q * s;

		tmp = old_t;
		old_t = t;
		t = tmp - q * t;
	}
	x = old_s;
	y = old_t;
	return old_r;*/
}

long long GetInverse(long long n, long long p) {
	long long gcd, x, y;
	gcd = GCDExtended(n, p, x, y);
	if ((n * x + p * y) % p != gcd || gcd != 1) {
		return -1;
	} else {
		return x % p;
	}
}

EPoint::EPoint(void) {
	this->SetInf();
}
EPoint::EPoint(long long x, long long y) {
	//cout << "IN: (" << x << "; " << y << ")" << endl;
	//cout << "EPOINT:IN" << endl;
	if (x == INF || y == INF) {
		this->SetInf();
		return;
	}
	//cout << "EPOINT 1" << endl;
	x %= ECURVE_P;
	y %= ECURVE_P;
	while (x < 0) {
		x += ECURVE_P;
	}
	//cout << "EPOINT 2" << endl;
	while (y < 0) {
		y += ECURVE_P;
		//cout << y << endl;
	}
	//cout << "EPOINT 3" << endl;
	this->X = x % ECURVE_P;
	//cout << "EPOINT 4" << endl;
	this->Y = y % ECURVE_P;
	//cout << "EPOINT:OUT" << endl;
}
EPoint::EPoint(EPoint *sample) {
	//*sample %= ECURVE_P;
	this->X = sample->X;
	this->Y = sample->Y;
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
	//cout << "POINT:IN" << endl;
	if (pnt1 == -pnt2) {
		return EPoint();
	}
	//cout << "POINT 1" << endl;
	if (pnt1.X == INF || pnt1.Y == INF) {
		return pnt2;
	}
	//cout << "POINT 2" << endl;
	if (pnt2.X == INF || pnt2.Y == INF) {
		return pnt1;
	}
	//cout << "POINT 3" << endl;

	long long m = 1;
	//cout << "==+++===" << endl;
	if (pnt1 != pnt2) {
		//cout << "POINT 3.1.1" << endl;
		//m = (TDouble) (pnt1.Y - pnt2.Y) / (TDouble) (pnt1.X - pnt2.X);
		m = (pnt1.Y - pnt2.Y) * GetInverse(pnt1.X - pnt2.X, ECURVE_P);
		//cout << "POINT 3.1.2" << endl;
	} else {
		//cout << "POINT 3.2.1" << endl;
		//m =(TDouble) (3 * pnt1.X*pnt1.X + ECURVE_A) / (TDouble) (2 * pnt1.Y);
		m = (3 * pnt1.X*pnt1.X + ECURVE_A) * GetInverse(2 * pnt1.Y, ECURVE_P);
		//cout << "POINT 3.2.2" << endl;
	}
	//cout << "POINT 4" << endl;
	m %= ECURVE_P;
	//cout << "POINT 5" << endl;
	//cout << "m = " << m << endl;
	long long xn = m*m - pnt1.X - pnt2.X;
	//cout << "POINT 6" << endl;
	//cout << "xn = " << xn << endl;
	long long yn = pnt1.Y + m * (xn - pnt1.X);
	//cout << "POINT:OUT" << endl;
	//cout << "POINTRES: (" << xn << ", " << -yn
	//cout << "yn = " << yn << endl;
	return EPoint(xn, -yn);
}	
EPoint operator -(const EPoint &pnt1, const EPoint &pnt2) {
	return pnt1 + (-pnt2);
}
EPoint operator *(const long long &num, const EPoint &pnt) {
	if (num == 0) {
		return EPoint(INF, INF);
	}
	if (num == 1) {
		return pnt;
	}
	long long mid = num / 2;
	return pnt * mid + pnt * (num - mid);
}
EPoint operator *(const EPoint &pnt, const long long &num) {
	return num * pnt;
}
EPoint operator %(const EPoint &pnt, const long long &p) {
	//return EPoint(0, 0);
	long long xn = pnt.X;
	long long yn = pnt.Y;
	while (xn < 0) {
		xn += p; 
	}
	while (yn < 0) {
		yn += p;
	}
	return EPoint(xn, yn);
}
