#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "interpolation.h"
#include "l_exception.h"
#include "point.h"
#include "my_math.h"

using namespace std;

Interpolation::Interpolation(Point *points_, int n, Real eps) {
	this -> points = (Point*)malloc(n * sizeof(Point));
	this -> eps = eps;
	this -> n = n;

	if(n < 2) {
        throw L_exception(NA_TOO_LITTLE, "Too little points to compute");
    }
		
	begin = points_[0].get_X();
    end = points_[0].get_X();

    for(int i = 0; i < n; i++) {
    	(this -> points)[i] = points_[i];
        
        if(points_[i].get_X() < begin) {
        	begin = points_[i].get_X();
        }
        if(points_[i].get_X() > end) {
        	end = points_[i].get_X();
        }
	}
	qsort(this -> points, n, sizeof(Point), Point::compare);

        for(int j = 0; j < n - 1; j++) {
        	if(compareReal((this -> points)[j].get_X(), (this -> points)[j + 1].get_X(), eps) == 0) {
            	throw new L_exception(NA_ABSCISSA, "Two points have equal abscissa");
            }
       	}
}

Real Interpolation::inter_lagrange(Real x) {
	Real value = 0; 
	Real product;

	if((x > this -> end) || (x < this -> begin)) {
		throw L_exception(NA_SEGMENT, "X is out of segment");
	}

	for(int i = 0; i < this -> n; i++) {
		product = 1;
		for(int j = 0; j < this -> n; j++) {
			if(j == i) {
				continue;
			}
			product *= (x - (this -> points)[j].get_X()) / ((this -> points)[i].get_X() - (this -> points)[j].get_X());
		}
		value += (this -> points)[i].get_Y() * product;
	}

	return value;
}

Interpolation::~Interpolation() {
	free(this -> points);
}
