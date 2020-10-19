#ifndef LAB1_COMMENT_H
#define LAB1_COMMENT_H

#include "defs.h"

struct comment {
  char username[STR_SIZE], text[TEXT_SIZE];
  size_t next;
  float score;
};


#endif //LAB1_COMMENT_H
