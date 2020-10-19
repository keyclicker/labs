#ifndef LAB1_CAFFE_SHOP_H
#define LAB1_CAFFE_SHOP_H

#include "defs.h"
#include <stddef.h>

struct caffe_shop {
  char name[STR_SIZE], address[STR_SIZE];
  size_t first_comment, comments_count;
  float score;
};

#endif //LAB1_CAFFE_SHOP_H
