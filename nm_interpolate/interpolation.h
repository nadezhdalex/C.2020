#ifndef INTERPOLATION
#define INTERPOLATION
#include "point.h"

class Interpolation {
    private:
		Point *points;
		Real begin, end, eps;
		int n;
    public:
		Interpolation(Point *points_, int n, Real eps);
		~Interpolation();
    	Real inter_lagrange(Real x);
};

#endif //INTERPOLATION
