#include "stdio.h"
#include "math.h"
#include "functions.c"

#define N 1000 // number of vertices
#define EPS 4. / N
#define ANG_EPS 0.001
#define BINS_EPS 0.00001
#define INF 1E18

/*Структура Вектор с основными операциями: сложение, вычитание, умножение на число, вычисления длины, вычисление направляющего вектора, магнитуды, скалярного прозведения, векторного произведение, "правого"("левого") перпендикуляра.*/
struct Vector {
	double x;
	double y;
};

struct Vector add(struct Vector a, struct Vector b) {
    return (struct Vector) {a.x + b.x, a.y + b.y};
}

struct Vector sub(struct Vector a, struct Vector b) {
    return (struct Vector) {a.x - b.x, a.y - b.y};
}

struct Vector mult(struct Vector a, double num) {
    return (struct Vector) {a.x * num, a.y * num};
}

double len(struct Vector a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

struct Vector dir(struct Vector a) {
    return (struct Vector) {a.x / len(a), a.y / len(a)};
}

struct Vector dir_mag(struct Vector a, double mag) {
    return mult(dir(a), mag);
}

double dot(struct Vector a, struct Vector b) {
    return a.x * b.x + a.y * b.y;
}

double cross(struct Vector a, struct Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Vector left(struct Vector a) {
    return (struct Vector) {-a.y, a.x};
}

struct Vector right(struct Vector a) {
    return (struct Vector) {a.y, -a.x};
}
/*
Функция возвращает координаты точки - проекции на данную прямую данной точки
Входное значение: точка, точка и направляющий вектор.
Выходное значение: точка.
*/
struct Vector projection_on_line(struct Vector A, struct Vector dir, struct Vector L) {
    double Square = cross(sub(A, L), dir);
    double dist_to_line = Square / len(dir);
    return add(A, dir_mag(left(dir), dist_to_line));
}
/*
Функция возвращает минимальное (максимальное) из двух чисел
Входное значение: два числа.
Выходное значение: минимальное (максимальное) число.
*/
double min(double m, double n);
double max(double m, double n);

/*
Функция записывает в массив все точки с шагом EPS.
Входные значение: массив из N элементов.
Выходное значение: нет.
*/
void build_n_gon(struct Vector n_gon[]);

/*
Функция возвращает площадь мноугоугольника.
Входные значение: массив из N элементов.
Выходное значение: площадь.
*/
double n_gon_square(struct Vector n_gon[]);

/*
Функция записывает в массив все точки, находящиеся в одной полуплоскости относительно данной прямой, а остальные записывает как проекцию на данную прямую.
Входные значение: массив из N элементов, точка и направляющий вектор, массив-результат.
Выходное значение: нет.
*/
void intersect_with_semi_plane(struct Vector n_gon[], struct Vector dir, struct Vector L, struct Vector res[]);

/*
Функция находит прямую, перпендикулярную данной, которая делит многоугольник пополам. (данная прямая проходит через начало координат)
Входные значение: массив из N элементов, направляющий вектор.
Выходное значение: длина вектора, параллельного данному. (если отложить этот вектор от начала координат - получим точку, через которую проведем искомую прямую).
*/
struct Vector divide_half(struct Vector n_gon[], struct Vector dir_v);

/*
Решение задачи реализовано в функции main. Меняем угол прямой проходящей через начало координат. С помощью функции divide_half находим перпендикулярную ей прямую (а точнее точку на главной прямой,
через которую должна пройти эта прямая), которая разделит мноугоугольник пополам. Далее снова пользуемся функцией divide_half, но уже относительно получившейся прямой.
Затем найдем площадь предполагаемой четверти. Если она минимальна - это и будет наш ответ. Если нет - поворачиваем главную прямую на небольшой угол и продолжаем цикл. 
*/
int main(void) {
	FILE *fout;
	struct Vector n_gon[N];
	fout = fopen("output.txt", "w");
    if(fout == NULL) {
        printf("Could not open file output.txt\n");
        return -1;
    }
	
    build_n_gon(n_gon);
    double S = n_gon_square(n_gon);
    double ang = 0;
    double mind = INF;
    struct Vector A, B, C, D;
    while (ang < PI / 2) {
        struct Vector main_dir = {cos(ang), sin(ang)};
        struct Vector p1 = divide_half(n_gon, main_dir);
        struct Vector p2 = divide_half(n_gon, left(main_dir));
        struct Vector tmp1[N], tmp2[N];
        intersect_with_semi_plane(n_gon, left(main_dir), p1, tmp1);
        intersect_with_semi_plane(tmp1, main_dir, p2, tmp2);
        if (fabs(S / 4 - n_gon_square(tmp2)) < mind) {
            A = p1;
            B = add(p1, left(main_dir));
            C = p2;
            D = add(p2, main_dir);
            mind = fabs(S / 4 - n_gon_square(tmp2));
        }
        ang += ANG_EPS;
    }
    fprintf(fout, "(%g, %g)\n(%g, %g)\n\n(%g, %g)\n(%g, %g)\n", A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y);
    fclose(fout);
    return 0;
}

double min(double m, double n) {
	if(m - n > EPS) {
		return n;
	}
	else {
		return m;
	}
}

double max(double m, double n) {
	if(m - n > EPS) {
		return m;
	}
	else {
		return n;
	}
}

void build_n_gon(struct Vector n_gon[]) {
    for (int i = 0; i < N / 4; i++) {
        double t = EPS * i;
        n_gon[i] = (struct Vector) {t, min(X(t), Y(t))};
        n_gon[3 * N / 4 - i]= (struct Vector) {t, max(X(t), Y(t))};
    }
    double step_1 = (max(X(1), Y(1)) - min(X(1), Y(1))) / (N / 4);
    double step_0 = (max(X(0), Y(0)) - min(X(0), Y(0))) / (N / 4);
    for (int i = 0; i < N / 4 + 1; i++) {
        n_gon[N / 4 + i] = (struct Vector) {1, min(X(1), Y(1)) + step_1 * i};
    }
    for (int i = 1; i < N / 4 + 1; i++) {
        n_gon[N - i] = (struct Vector) {0, min(X(0), Y(0)) + step_0 * i};
    }
}

double n_gon_square(struct Vector n_gon[]) {
    double S = 0;
    for (int i = 0; i < N; i++) {
        int j = (i + 1) % N;
        S += cross(n_gon[i], n_gon[j]);
    }
    return fabs(S / 2);
}


void intersect_with_semi_plane(struct Vector n_gon[], struct Vector dir, struct Vector L, struct Vector res[]) {
    for (int i = 0; i < N; i++) {
        struct Vector point = n_gon[i];
        if (cross(sub(point, L), (dir)) > 0) {
            res[i] = point;
        } else {
            res[i] = projection_on_line(point, dir, L);
        }
    }
}

struct Vector divide_half(struct Vector n_gon[], struct Vector dir_v) {
    double l = INF;
    double r = -INF;
    double S = n_gon_square(n_gon);
    for (int i = 0; i < N; i++) {
        struct Vector point = n_gon[i];

        double point_proj = dot(projection_on_line(point, dir_v, (struct Vector) {0, 0}), dir_v) / len (dir_v);
        if (point_proj > r) {
            r = point_proj;
        }
        if (point_proj < l) {
            l = point_proj;
        }
    }

    while (fabs(r - l) > BINS_EPS) {
        double m = (r + l) / 2;
        struct Vector point = dir_mag(dir_v, m);
        struct Vector tmp[N];
        intersect_with_semi_plane(n_gon, left(dir_v), point, tmp);
        if (n_gon_square(tmp) < S / 2) {
            r = m;
        } else {
            l = m;
        }
    }
    return dir_mag(dir_v, l);
}
