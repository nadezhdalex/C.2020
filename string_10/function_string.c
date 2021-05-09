#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "function_string.h"
static void find_and_replace(struct Map *map, long int map_len, char *word) {
    for(int i = 0; i < map_len; i++) {
        if(string_cmp(map[i].key, word) == 0) {
            int new_len = string_length(map[i].value);
            word = (char*)realloc(word, new_len + 1);
            word[new_len] = '\0';
            string_copy(word, map[i].value);
        }
    }
}

static void remove_elem(struct Map *map, long int *map_len, char *word) {
    for(int i = 0; i < *map_len; i++) {
        if(string_cmp(map[i].key, word) == 0) {
            int new_len_key = string_length(map[*map_len - 1].key);
            int new_len_value = string_length(map[*map_len - 1].value);
            map[i].key = (char*)realloc(map[i].key, new_len_key + 1);
            map[i].key[new_len_key] = '\0';
            map[i].value = (char*)realloc(map[i].value, new_len_value + 1);
            map[i].value[new_len_value] = '\0';
            string_copy(map[i].key, map[*map_len - 1].key);
            string_copy(map[i].value, map[*map_len - 1].value);
            free(map[*map_len - 1].key);
            free(map[*map_len - 1].value);
            (*map_len)--;
            break;
        }
    }

}

static void freeMap(struct Map *map, long int map_len) {
    for(long int i = 0; i < map_len; i++) {
        free(map[i].key);
        free(map[i].value);
    }
    free(map);
}

void function_define(FILE *fin, FILE *fout) {
    struct Map *map = NULL;
    long int map_len = 0;
    char *string;
    char *word = NULL;
    int curr_len = 0;
    int is_new_word = 1;
    int end_symbol = 0;
    long int len = 0;
    int word_count = 0;
    int define_flag = 0;
    char symbol;
    char *def = "#define";
    char *und = "#undef";
    while((string = read_string(fin)) && (string != NULL)) {
        len = string_length(string);
        word_count = 0;
        define_flag = 3;
        if(string[len - 1] == '\n')
            end_symbol = 1;
        else
            end_symbol = 0; //строка в конце файла

        for(long int i = 0; i < len - end_symbol; i++) {
            symbol = string[i];
            if(symbol != ' ') {
                if(is_new_word)
                    word_count++;
            }
            //Достигаем либо конца строки, либо пробела
            if((i == len - end_symbol - 1) && (symbol != ' '))
                curr_len++;

            if((symbol == ' ') || (i == len - end_symbol - 1)) {
                if(curr_len > 0) {
                    word = (char*)realloc(word, curr_len + 1);
                    word[curr_len] = '\0';
                    if(word == NULL)
                        printf("Failed");
                    for(int j = 0; j < curr_len; j++) {
                        word[j] = string[i - curr_len + j];
                    }
                    if(word_count == 1) {
                        if(string_cmp(def, word) == 0) {
                            define_flag = 1;
                        }
                        else if(string_cmp(und, word) == 0) {
                            define_flag = -1;
                        }
                        else {
                            define_flag = 0;
                        }
                    }
                    if(word_count == 2 && define_flag != 0) {
                        if(define_flag == 1) {
                            map = (struct Map*)realloc(map, map_len + 1);
                            map[map_len - 1].key = (char*)realloc(map[map_len - 1].key, curr_len + 1);
                            map[map_len - 1].key[curr_len] = '\0';
                            string_copy(map[map_len - 1].key, word);        
                        }
                        else {
                            remove_elem(map, &map_len, word);    
                        }
                    }
                    if(word_count == 3 && define_flag == 1) {
                        map[map_len - 1].value = (char*)realloc(map[map_len - 1].value, len - end_symbol - i + 1);
                        for(int k = 0; k < len - end_symbol - i; k++) {
                            map[map_len - 1].value[k] = string[i + k + 1];
                        }
                        map[map_len - 1].value[len - end_symbol] = '\0';
                        break;
                    }
                    if(define_flag == 0) {
                        find_and_replace(map, map_len, word);
                    }          
                }
                is_new_word = 1;
                curr_len = 0;
            }
            else {
                is_new_word = 0;
                curr_len++;
            }
        }
        fprintf(fout, "%s", string);
        free(word);
        free(string);
    }
    freeMap(map, map_len);
	free(def);
	free(und);
}
