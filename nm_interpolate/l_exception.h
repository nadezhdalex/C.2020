#ifndef L_EXCEPTION
#define L_EXCEPTION
#include <string>
#define NA_OK 1 // ошибок нет
#define NA_TOO_LITTLE -1 // количество точек меньше 2
#define NA_ABSCISSA -2 // одинаковые точки
#define NA_SEGMENT -3 // значение выходит за пределы отрезка

using namespace std;

class L_exception {
	private:
		int cod;
		string mes;
	public:
		L_exception(int code_, string message_);
		string message() const;
		int code() const;
};
#endif // L_EXCEPTION
