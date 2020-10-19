#ifndef LAB1_DATABASE_H
#define LAB1_DATABASE_H

#include "caffe_shop.h"
#include "comment.h"

void insert_cs(char *name, char *address);
void insert_com(char *cs_name, char *username, char *text, float score);

struct caffe_shop* get_cs(char *name);
struct comment* get_com(struct caffe_shop *cs, size_t ind);

void print_cs(struct caffe_shop *cs);
void print_com(struct comment *com);

void clear();

#endif //LAB1_DATABASE_H
