#include <stdio.h>
#include <stdlib.h>
#include "function_file.h"
#include <ftw.h>
#include <string.h>

char **list_file1 = NULL;
long int len_list1 = 0;
char **list_file2 = NULL;
long int len_list2 = 0;
char *dir1 = NULL;
char *dir2 = NULL;

/*
	Функция по заданному пути возвращает название файла. После вызова требует очистки памяти.
*/
static char* file_name(const char *fpath) {
    int i = strlen(fpath);
    char *new_filename = NULL;
    while((i >= 0) && (fpath[i] != '/'))
	i--;
    new_filename = (char*)malloc((strlen(fpath) - i) * sizeof(char));
    strcpy(new_filename, fpath + i + 1);
    return new_filename;
    /*char *finame = NULL;
    char *last_slash = strrchr(fpath, '/');
    if(last_slash != NULL) {
        finame = last_slash + 1;
    }
    else {
        finame = (char*)fpath;
    }
    return finame;
   */ 
}

/*
	Функция по заданному пути добавляет новое имя в список файлов.
*/
static void add_to_list(const char *fpath, char **list, long int *len_list) {
    char *finame = file_name(fpath);
    int len_finame = strlen(finame);
    (*len_list)++;
    list = (char**)realloc(list, (*len_list) * sizeof(char*));
    list[(*len_list) - 1] = (char*)malloc((len_finame + 1) * sizeof(char)); 
    strcpy(list[(*len_list) - 1], finame);
    free(finame);
}

/*
	Функция очистки памяти для списка.
*/
static void freeList(char **list, long int len_list) {
    for(long int i = 0; i < len_list; i++) {
        free(list[i]);
    }
    free(list);
}

/*
	Функция, передаваемая функции ftw, в случае, если путь, обозначает файл, записывает его в соответствующий список.
*/
int fn(const char *fpath, const struct stat *sb, int typeflag) {
    if(typeflag != FTW_F) {
        return 0;
    }

    if(strncmp(fpath, dir1, strlen(dir1)) == 0) {
        add_to_list(fpath, list_file1, &len_list1);
    }
    if(strncmp(fpath, dir2, strlen(dir2)) == 0) {
        add_to_list(fpath, list_file2, &len_list2);
    }

    return 0;
    }
/*
	Функция, передаваемая функции qsort. (работает также как и strcmp).
*/
static int compare_strings(const void *str1, const void *str2) {
    return strcmp(*(char **)str1, *(char **)str2);
}
/*
	Функция печатает файлы, которые есть в первой директории и которых нет во второй.
*/
static void print_dif_for_one_file(const char *dir1_name, char **list1, int list1_len, 
    char **list2, int list2_len) {

    printf("%s: ", dir1_name);
    int j = 0;
    for (int i = 0; i < list1_len; i++) {
        int belongs = 0;
        if ((i > 0) && (strcmp(list1[i], list1[i - 1]) == 0)) {
            continue;
        }
        while ((j < list2_len) && !(strcmp(list1[i], list2[j]) < 0)) {
            if (strcmp(list1[i], list2[j]) == 0) {
                belongs = 1;
                break;
            }
            j++;
        }

        if (belongs == 0) {
            printf("%s ", list1[i]);
        }
    }
    printf("\n");
}

void difference(const char *directory1, const char *directory2) {
    dir1 = (char*)malloc((strlen(directory1) + 1) * sizeof(char));
    strcpy(dir1, directory1);
    dir2 = (char*)malloc((strlen(directory2) + 1) * sizeof(char));
    strcpy(dir2, directory2);

    ftw(dir1, fn, 10);
    ftw(dir2, fn, 10);
    qsort(list_file1, (size_t)len_list1, sizeof(char *), compare_strings);
    qsort(list_file2, (size_t)len_list2, sizeof(char *), compare_strings);
    print_dif_for_one_file(dir1, list_file1, len_list1, list_file2, len_list2);
    print_dif_for_one_file(dir2, list_file2, len_list2, list_file1, len_list1);
    freeList(list_file1, len_list1);
    freeList(list_file1, len_list1);
    free(dir1);
    free(dir2);
}
