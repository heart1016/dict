#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <dirent.h>
#include "dict.h"

int main(int argc, char *argv[])
{
    const char *pathname = "/Users/heart/Downloads/aria2c/dict/init_dict/dict.txt";
    struct DICT *p;
    int size;
    int n;
    char trans[1024];
    char key[1024];

    if (2 > argc) {
        printf("./main -text                The default word library is initialized\n");
        printf("./main -f    pathname       The custom  word library is initialized\n");
        return 0;
    }

    if (strcmp(argv[1], "-text") == 0) {

        size = dict_count(pathname);
        if (0 == size) {
            printf("dict_size error");
            exit(1);
        }

        n = dict_init(pathname, &p, size);
        if (n != size) {
            perror("dict_init error");
            exit(1);
        }

        while (1) {
            memset(trans, 0, sizeof(trans));
            memset(key, 0, sizeof(key));
            scanf("%s", key);

            if (strcmp(key, "exit001") == 0) {
                break;
            }

            if (dict_search(p, key, trans, size)) {
            } else {
                printf("not found\n");
            }
        }
    }

    if (strcmp(argv[1], "-f") == 0) {
        size = dict_count(argv[2]);
        if (0 == size) {
            printf("dict_size error");
            exit(1);
        }

        n = dict_init(argv[2], &p, size);
        if (n != size) {
            perror("dict_init error");
            exit(1);
        }

        while (1) {
            memset(trans, 0, sizeof(trans));
            memset(key, 0, sizeof(key));
            scanf("%s", key);

            if (strcmp(key, "exit001") == 0) {
                break;
            }

            if (dict_search(p, key, trans, size)) {
            } else {
                printf("not found\n");
            }
        }
    }

    dict_free(p, size);

    return 0;
}
