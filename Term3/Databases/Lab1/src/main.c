#include <stdio.h>

#include "../include/database.h"

int main() {
  clear();

  size_t bucco = insert_cs("Bucco", "Chernivtsi");
  size_t novacava = insert_cs("NovaCava", "Kyiv");
  size_t kavoman = insert_cs("Kavoman", "Lviv");
  size_t coffeshop = insert_cs("CoffeeShop", "Amsterdam");
  size_t kavahusta = insert_cs("KavaHusta", "Ternopil");

  insert_com(bucco, "keyclicker", "Pretty good!", 4);
  size_t mexalik_com = insert_com(bucco, "mexalik", "I regret going to this place!", 1);
  insert_com(novacava, "stefanio", "Best place in Kyiv!", 5);
  insert_com(novacava, "nalexxx", "Nothing special", 3);
  size_t gleb_com = insert_com(novacava, "gleb", "stefanio, you have terrible taste", 2);
  insert_com(kavahusta, "ostapmk", "Stupid name, bad caffe.", 2);

  ut_cs();
  ut_com();

  del_cs(bucco);
  del_com(novacava, gleb_com);

  ut_cs();
  ut_com();

  size_t spacebucks = insert_cs("SpaceBucks", "Kyiv");
  size_t keycom = insert_com(spacebucks, "keyclicker", "Overrated scum", 3);

  ut_cs();
  ut_com();

  update_cs(bucco, "Kashtanooko", "Kyiv");
  update_com(spacebucks, keycom, "keyclicker", "Best place in the city!", 6);

  ut_cs();
  ut_com();


  struct caffe_shop *cs = get_cs(novacava);
  struct comment *com = get_com(bucco, 1);

  print_cs(cs);
  print_com(com);


  printf("Hello, World!\n");
  return 0;
}
