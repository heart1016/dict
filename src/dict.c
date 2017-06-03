#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dict.h"

int dict_count(const char *pathname)
{
    FILE *fp;
    char *n;
    char buf[1024];
    int i = 0;

    fp = fopen(pathname, "r");
    if (NULL == fp) {
        perror("fopen error");
        exit(1);
    }

    while ((n = fgets(buf, sizeof(buf), fp)) != NULL) {
        i++;
    }

    return i/2;
}

int dict_init(const char *pathname, struct DICT **word, int size)
{
    FILE *fp;
    char buf[1024];
    int i = 0;
    int j = 0;
    size_t len;
    char *str;
    char *sstr;

    fp = fopen(pathname, "r");
    if (NULL == fp) {
        perror("fopen error");
        exit(1);
    }

    *word = (struct DICT *)malloc(sizeof(struct DICT)*size);
    memset(*word, 0, sizeof(struct DICT)*size);
    struct DICT *p = *word;

    while (!feof(fp)) {
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        len = strlen(buf);

        if (len > 0) {
            p[i].key = (char *)malloc(len);
            memset(p[i].key, 0, len);
            str = strtok(buf, "#\n");
            strcpy(p[i].key, str);
        }

        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), fp);
        len = strlen(buf);

        j=0;
        if (len > 0) {
            p[i].trans = (char **)malloc(sizeof(char*)*len);
            memset(p[i].trans, 0, len);
            sstr = strtok(buf, ":@");

            while ((sstr = strtok(NULL, ":@")) != NULL) {
                p[i].trans[j] = (char *)malloc(sizeof(char)*len);
                strcpy(p[i].trans[j], sstr);
                j++;
            }
            p[i].ntrans = j;
        }
        i++;
    }
    fclose(fp);

    return i-1;
}

int dict_search(const struct DICT *p, const char *key, char *trans, int size)
{
    int i = 0;
    int j = 0;

    for (i=0;i<size;i++) {
        if ((p[i].key == NULL) || (p[i].trans == NULL)) {
            continue;
        }

        if ((strcmp(p[i].key, key)) == 0) {
            for (j=0;j<p[i].ntrans;j++) {
                strcpy(trans, p[i].trans[j]);
                printf("%s\n", trans);
            }
            return 1;
        }
    }

    return 0;
}

void dict_free(struct DICT *p, int size)
{
    int i, j;

    for (i=0;i<size;i++) {
        free(p[i].key);
        for (j=0;j<p[i].ntrans;j++) {
            free(p[i].trans[j]);
        }
    }
    free(p);
}
