#define NA_OK 1
#define NA_FILENAME -1
#define NA_CAN_NOT_OPEN_FILE -2
#define NA_WRONG_NUMBER	-3
#define NA_MEMORY -4
#define NA_NULLPOINTER -5
#define NA_MATR_IS_SINGULAR -6
#define NA_NOT_QUADRATIC -7

struct NAError {
	int code;
	char *mes;
};
