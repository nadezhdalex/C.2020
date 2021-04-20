#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "L_exception.h"

L_exception::L_exception(int code_, string message_) {
	this -> code = code_;
	this -> message = message_;
}

string L_exception::message() const {
	return this -> message;
}

int L_exception::code() const {
	return this -> code;
}
