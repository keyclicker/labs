#ifndef LAB1_COMMENT_H
#define LAB1_COMMENT_H

#include "defs.h"
#include <stddef.h>
#include <stdbool.h>

struct comment {
  bool deleted;
  char username[STR_SIZE], text[TEXT_SIZE];
  size_t pos;
  long next;
  float score;
};


#endif //LAB1_COMMENT_H
