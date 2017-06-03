#ifndef _DICT_H
#define _DICT_H

struct DICT
{
    char *key;          //保存单词
    int ntrans;         //记录单词解释个数
    char **trans;
};

int dict_count(const char *pathname);
int dict_init(const char *pathname, struct DICT **word, int size);
int dict_search(const struct DICT *p, const char *key, char *trans, int size);
void dict_free(struct DICT *p, int size);
#endif
