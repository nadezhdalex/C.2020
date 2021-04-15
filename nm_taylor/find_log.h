typedef double Real;
#define ITERATION 100 // количество итераций
#define EPS 0.0003
#define NA_OK 1 // ошибок нет
#define NA_RANGE -1 // неверный отрезок
#define NA_CONVERGE -2 // превышено количество итераций


/*
    Функция вычисляет значение ln(x) в заданной точке x и с заданной точностью ε суммированием ряда Тейлора.
    Параметры:
        x: заданная точка
        eps: заданная точность
        err: код ошибки.
	
	Возвращаемое значение:
		Функция возвращает f(x) и записывает код ошибки.	
*/
int almost_equal(Real x, Real y);
Real find_log(Real x, Real eps, int *err);
