#ifndef INTERPOLATION
#define INTERPOLATION
#define NA_OK 1 // ошибок нет
#define NA_TOO_LITTLE -1 // количество точек меньше 2
#define NA_ABSCISSA -2 // одинаковые точки
#define NA_SEGMENT -3 // значение выходит за пределы отрезка

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
