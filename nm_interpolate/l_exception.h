#ifndef L_EXCEPTION
#define L_EXCEPTION
#include <string>

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
