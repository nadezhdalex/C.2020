#include <stdio.h>
typedef double Real;
typedef unsigned int Natural;
typedef Natural (*PFunc)(Natural n, Real x);

/*
** Применяет заданную функцию f к аргументам n, x.
*/
Natural apply(PFunc f, Natural n, Real x);

/*
** Вычисляет свертку массива arr действительных чисел относительно функции f и начального значения n.
*/

Natural reduce(PFunc f, Natural n, Real *arr, Natural len);
