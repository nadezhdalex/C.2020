#define NA_OK 1
#define NA_FILENAME -1
#define NA_CAN_NOT_OPEN_FILE -2
#define NA_WRONG_NUMBER	-3
#define NA_MEMORY -4
#define NA_NULLPOINTER -5

struct NAError {
	int code;
	char *mes;
};
