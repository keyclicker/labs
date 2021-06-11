#ifndef LAB1_DATABASE_H
#define LAB1_DATABASE_H

#include "caffe_shop.h"
#include "comment.h"
#include "index_struct.h"

size_t insert_cs(char *name, char *address);
size_t insert_com(size_t cs_key, char *username, char *text, float score);

struct caffe_shop* get_cs(size_t key);
struct comment* get_com(size_t key, size_t ind);

void print_cs(struct caffe_shop *cs);
void print_com(struct comment *com);

void update_cs(size_t key, char *name, char *address);
void update_com(size_t cs_key, size_t pos,
                char *username, char *text, float score);

void ut_cs();
void ut_com();

void del_cs(size_t key);
void del_com(size_t cs_key, size_t ind);

void clear();

#endif //LAB1_DATABASE_H
