#include "my_string.h"

int string_length(const char *string) {
    int len = 0;
    while(string[len] != '\0') {
        len++;
    }
    return len;
}

char* string_copy(char *copy, const char *string) {
	int len = string_length(string);
	for (int i = 0; i < len + 1; i++) {
		copy[i] = string[i];
	}
	return copy;
}

int string_cmp(const char *string1, const char *string2) {
	int i = 0;
	int len = string_length(string1);
	while((string1[i] == string2[i]) && (i < len)) {
		i++;
	}

	return string1[i] - string2[i];
}

char* read_string(FILE *stream) {
    int bufsize = 1024;
    char buf[bufsize];
    int buf_len = 1, curr_len = 1;
    char *result = NULL;

    do {
		if(fgets(buf, bufsize, stream) != buf) {
            return NULL;
       	}
       	
		buf_len = string_length(buf);
		result = (char*)realloc(result, curr_len + buf_len);
		string_copy(&result[curr_len - 1], buf);
		curr_len += buf_len;

		if((curr_len > 1) && (result[curr_len - 2] == '\n')) {
	    	result[curr_len - 2] = '\0';
	    	result = (char*)realloc(result, curr_len - 1);
	    	break;
	    }
	} while (buf_len > 0);

	return result;
}
