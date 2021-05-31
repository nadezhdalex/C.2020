#include "my_string.h"
#include "string.h"
int string_length(const char *string) {
    int len = 0;
    while(string[len] != '\0') {
        len++;
    }
    return len;
}


int string_cmp(const char *string1, const char *string2) {
	int i = 0;
	int len = string_length(string1);
	while((string1[i] == string2[i]) && (i < len)) {
		i++;
	}

	return string1[i] - string2[i];
}
void string_copy(char *copy, const char *string) {
	while(*string) {
		*(copy++) = *(string++);
	}
	*copy = '\0';
}


/*char *read_string(FILE *stream) {
    char buf[1024];
    char *s = fgets(buf, 1024, stream);
    if(s) {
        int len = strlen(s);
        int tmp = 0;
		int past_len = 0;
        char *res = malloc(len+1);
        while(s) {
            strcpy(res+past_len, s);
            if(s[strlen(s)-1] == '\n') break;
            s = fgets(buf, 1024, stream);
            if (s) {
                tmp = strlen(s);
                past_len = len;
                len += tmp;
                res = realloc(res, len+1);
            }
        } 
        if(res[strlen(res)-1] == '\n'){
            res[strlen(res)-1] = '\0';
        }
        return res;
    } 
    return NULL;
}
*/

char* read_string(FILE *stream) {
    int bufsize = 1024;
    char buf[bufsize];
    buf[0] = '\0';
    int buf_len = 1, curr_len = 0;
    char *result = NULL;

    do {
		if(fgets(buf, bufsize, stream) != buf) {
			return result;
		}
		buf_len = string_length(buf);
		result = (char*)realloc(result, curr_len + buf_len + 1);
		string_copy(&result[curr_len], buf);
		curr_len += buf_len;

		if(result[curr_len - 1] == '\n') {
			result[curr_len -1] = '\0';
	    		break;
	    }
	} while (buf_len > 0);

	return result;
}

