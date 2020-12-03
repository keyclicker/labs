#include "../include/database.h"
#include "../include/caffe_shop.h"
#include "../include/comment.h"
#include "../include/defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t pos = 0;

void insert_cs(char *name, char *address) {
  struct caffe_shop cs;

  strcpy(cs.name, name);
  strcpy(cs.address, address);

  cs.comments_count = 0;
  cs.first_comment = -1;
  cs.score = 0;

  FILE *cs_fl = fopen(CS_FL,"ab");
  FILE *cs_ind = fopen(CS_IND,"ab");

  unsigned int s_size = strlen(name);
  fwrite(&s_size, sizeof(unsigned int), 1, cs_ind);
  fwrite(name, sizeof(char), s_size + 1, cs_ind);

  fwrite(&cs, sizeof(struct caffe_shop), 1, cs_fl);

  print_cs(&cs);

  fclose(cs_fl);
  fclose(cs_ind);
}

void insert_com(char *cs_name, char *username, char *text, float score) {
  struct caffe_shop *cs = get_cs(cs_name);

  struct comment com;
  strcpy(com.username, username);
  strcpy(com.text, text);
  com.next = -1;
  com.score = score;

  FILE *com_fl = fopen(COM_FL,"ab");
  long pos = ftell(com_fl);


  if (cs->first_comment == -1)
    cs->first_comment = pos;
  else {
    struct comment *c = get_com(cs, cs->comments_count - 1);
    //c->next
  }
  cs->comments_count++;
}

struct caffe_shop* get_cs(char *name) {
  FILE *cs_ind = fopen(CS_IND,"rb");

  size_t pos = 0;
  while (!feof(cs_ind)) {
    unsigned int s_size = strlen(name);
    char str[STR_SIZE];

    fread(&s_size, sizeof(unsigned int), 1, cs_ind);
    fread(str, sizeof(char), s_size + 1, cs_ind);

    if (!strcmp(str, name))
      break;
    pos++;
  }
  fclose(cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb");
  struct caffe_shop *cs = malloc(sizeof(struct caffe_shop));
  fseek(cs_fl, sizeof(struct caffe_shop) * pos, SEEK_SET);
  fread(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_fl);
  return cs;
}

void print_cs(struct caffe_shop *cs) {
  printf("\"%s\":\n"
         "  address = \"%s\"\n"
         "  comments_count = %i\n"
         "  first_comment = %i\n"
         "  score = %f\n\n",
         cs->name, cs->address,
         cs->comments_count,
         cs->first_comment, cs->score);
}

void clear() {
  fopen(CS_FL, "w");
  fopen(CS_IND, "w");
  fopen(COM_FL, "w");
}

struct comment *read_com(size_t ind) {
  FILE *com_fl = fopen(COM_FL,"rb");
  struct comment *cs = malloc(sizeof(struct comment));
  fseek(com_fl, sizeof(struct comment) * ind, SEEK_SET);
  fread(cs, sizeof(struct comment), 1, com_fl);
  fclose(com_fl);
}

struct comment *get_com(struct caffe_shop *cs, size_t ind) {
  struct comment *com = read_com(cs->first_comment);
  if (!ind) {
    return com;
  }
  else {
    for (size_t i = 0; i < ind; i++)
      com = read_com(com->next);
  }
  return com;
}
