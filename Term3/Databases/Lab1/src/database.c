#include "../include/database.h"
#include "../include/caffe_shop.h"
#include "../include/comment.h"
#include "../include/defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t pos = 0;

size_t insert_cs(char *name, char *address) {
  FILE *cs_fl = fopen(CS_FL,"ab");
  FILE *cs_ind = fopen(CS_IND,"ab");

  struct caffe_shop cs;

  strcpy(cs.name, name);
  strcpy(cs.address, address);

  cs.comments_count = 0;
  cs.first_comment = -1;
  cs.score = 0;
  cs.key = ftell(cs_ind) / sizeof(struct index_struct);
  cs.deleted = 0;

  struct index_struct is;

  is.key = cs.key;
  is.pos = ftell(cs_fl) / sizeof(struct caffe_shop);

  fwrite(&is, sizeof(struct index_struct), 1, cs_ind);
  fwrite(&cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_fl);
  fclose(cs_ind);

  ++pos;
  return is.key;
}

size_t insert_com(size_t cs_key, char *username, char *text, float score) {
  struct caffe_shop *cs = get_cs(cs_key);

  struct comment com;
  strcpy(com.username, username);
  strcpy(com.text, text);
  com.next = -1;
  com.score = score;
  com.deleted = 0;

  FILE *com_fl = fopen(COM_FL,"rb+");
  fseek(com_fl, 0, SEEK_END) / sizeof(struct comment);
  long fpos = ftell(com_fl) / sizeof(struct comment);

  com.pos = fpos;
  fwrite(&com, sizeof(struct comment), 1, com_fl);

  if (!cs->comments_count)
    cs->first_comment = fpos;
  else {
    struct comment *c = get_com(cs->key, cs->comments_count - 1);
    c->next = fpos;
    printf("%i, %i, %i\n",c->pos, cs->key, cs->comments_count - 1);
    fseek(com_fl, c->pos * sizeof(struct comment), SEEK_SET);
    fwrite(c, sizeof(struct comment), 1, com_fl);
  }

  cs->score = (float)(cs->score * cs->comments_count + com.score) / (cs->comments_count + 1);
  ++cs->comments_count;


  FILE *cs_ind = fopen(CS_IND,"rb");
  struct index_struct is;

  fseek(cs_ind, sizeof(struct index_struct) * cs->key, SEEK_SET);
  fread(&is, sizeof(struct index_struct), 1, cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb+");

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fwrite(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_fl);
  fclose(cs_ind);
  fclose(com_fl);

  return cs->comments_count;
}

struct caffe_shop* get_cs(size_t key) {
  FILE *cs_ind = fopen(CS_IND,"rb");
  struct index_struct is;

  fseek(cs_ind, sizeof(struct index_struct) * key, SEEK_SET);
  fread(&is, sizeof(struct index_struct), 1, cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb");
  struct caffe_shop *cs = malloc(sizeof(struct caffe_shop));

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fread(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_fl);
  fclose(cs_ind);
  return cs;
}

struct comment *read_com(size_t ind) {
  FILE *com_fl = fopen(COM_FL,"rb");
  struct comment *cs = malloc(sizeof(struct comment));
  fseek(com_fl, sizeof(struct comment) * ind, SEEK_SET);
  fread(cs, sizeof(struct comment), 1, com_fl);
  fclose(com_fl);
  return cs;
}

struct comment *get_com(size_t key, size_t ind) {
  struct caffe_shop *cs = get_cs(key);
  struct comment *com = read_com(cs->first_comment);
  if (!ind) {
    return com;
  }
  else if (com->next != -1) {
    for (size_t i = 0; i < ind && com->next != -1; i++)
      com = read_com(com->next);
  }
  return com;
}


void print_cs(struct caffe_shop *cs) {
  printf("\"%s\":\n"
         "  key = \"%i\",  address = \"%s\", score = %.2f\n"
         "  comments_count = %i, first_comment = %i, deleted = %i\n",
         cs->name,
         cs->key, cs->address,
         cs->comments_count,
         cs->first_comment, cs->score,
         cs->deleted);
}

void print_com(struct comment *com) {
  printf("  \"%s\": score = %.2f\n"
         "    text = \"%s\"\n"
         "    pos = %i, next = %i, deleted = %i\n",
         com->username,
         com->text, com->score,
         com->pos, com->next,
         com->deleted);
}

void ut_cs() {
  FILE *fcs = fopen(CS_FL,"r");
  printf("Printing \"%s\":\n", CS_FL);

  struct caffe_shop cs;;
  while (fread(&cs, sizeof(struct caffe_shop), 1, fcs) == 1) {
    if (!cs.deleted)
      print_cs(&cs);
  }
  printf("\n");
  fclose(fcs);
}

void ut_com() {
  FILE *fcom = fopen(COM_FL,"r");
  printf("Printing \"%s\":\n", COM_FL);

  struct comment com;
  while (fread(&com, sizeof(struct comment), 1, fcom) == 1) {
    if (!com.deleted)
      print_com(&com);
  }
  printf("\n");
  fclose(fcom);
}

void update_cs(size_t key, char *name, char *address) {
  FILE *cs_ind = fopen(CS_IND,"rb");
  struct index_struct is;

  fseek(cs_ind, sizeof(struct index_struct) * key, SEEK_SET);
  fread(&is, sizeof(struct index_struct), 1, cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb+");
  struct caffe_shop *cs = malloc(sizeof(struct caffe_shop));

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fread(cs, sizeof(struct caffe_shop), 1, cs_fl);

  strcpy(cs->name, name);
  strcpy(cs->address, address);

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fwrite(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_ind);
  fclose(cs_fl);
}

void update_com(size_t cs_key, size_t ind,
                char *username, char *text, float score) {
  struct comment *com = get_com(cs_key, ind);

  FILE *comf = fopen(COM_FL,"rb+");

  fseek(comf, com->pos * sizeof(struct comment), SEEK_SET);
  fread(com, sizeof(struct comment), 1, comf);

  com->score = com->score;
  strcpy(com->username, username);
  strcpy(com->text, text);

  fseek(comf, com->pos * sizeof(struct comment), SEEK_SET);
  fwrite(com, sizeof(struct comment), 1, comf);

  fclose(comf);
}

void del_cs(size_t key) {
  FILE *cs_ind = fopen(CS_IND,"rb");
  struct index_struct is;

  fseek(cs_ind, sizeof(struct index_struct) * key, SEEK_SET);
  fread(&is, sizeof(struct index_struct), 1, cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb+");
  struct caffe_shop *cs = malloc(sizeof(struct caffe_shop));

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fread(cs, sizeof(struct caffe_shop), 1, cs_fl);

  cs->deleted = 1;

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fwrite(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_ind);
  fclose(cs_fl);

  for (long i = cs->first_comment; i != -1;) {
    FILE *comf = fopen(COM_FL,"rb+");
    struct comment com;
    fseek(comf, i * sizeof(struct comment), SEEK_SET);
    fread(&com, sizeof(struct comment), 1, comf);
    com.deleted = 1;

    fseek(comf, i * sizeof(struct comment), SEEK_SET);
    fwrite(&com, sizeof(struct comment), 1, comf);
    i = com.next;

    fclose(comf);
  }

}

void del_com(size_t cs_key, size_t ind) {
  FILE *comf = fopen(COM_FL,"rb+");
  struct comment *com = get_com(cs_key, ind);

  fseek(comf, com->pos * sizeof(struct comment), SEEK_SET);
  fread(com, sizeof(struct comment), 1, comf);

  com->deleted = 1;

  fseek(comf, com->pos * sizeof(struct comment), SEEK_SET);
  fwrite(com, sizeof(struct comment), 1, comf);

  fclose(comf);

  FILE *cs_ind = fopen(CS_IND,"rb");
  struct index_struct is;

  fseek(cs_ind, sizeof(struct index_struct) * cs_key, SEEK_SET);
  fread(&is, sizeof(struct index_struct), 1, cs_ind);

  FILE *cs_fl = fopen(CS_FL,"rb+");
  struct caffe_shop *cs = malloc(sizeof(struct caffe_shop));

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fread(cs, sizeof(struct caffe_shop), 1, cs_fl);

  cs->score = (float)(cs->score * cs->comments_count - com->score) / (cs->comments_count - 1);
  --cs->comments_count;

  fseek(cs_fl, is.pos * sizeof(struct caffe_shop), SEEK_SET);
  fwrite(cs, sizeof(struct caffe_shop), 1, cs_fl);

  fclose(cs_ind);
  fclose(cs_fl);
}

void clear() {
  fopen(CS_FL, "w");
  fopen(CS_IND, "w");
  fopen(COM_FL, "w");
}

