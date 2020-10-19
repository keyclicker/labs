#include <stdio.h>

#include "../include/database.h"

int main() {
  clear();

  insert_cs("Bucco", "Chernivtsi");
  insert_cs("NovaCava", "Kiev");
  struct caffe_shop *cs = get_cs("NovaCava");

  print_cs(cs);


  printf("Hello, World!\n");
  return 0;
}
