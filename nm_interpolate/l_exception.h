#ifndef L_EXCEPTION
#define L_EXCEPTION
#include <string>

class L_exception {
	private:
		int code;
		string message;
	public:
		L_exception(int code_, string message_);
		string message() const;
		int code() const;
};
#endif // L_EXCEPTION
