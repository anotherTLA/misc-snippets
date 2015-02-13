#include "vector.h"
#include <stdio.h>

/* tests for vector. */
int main (int argc, char ** argv) {
  /* create using "constructors" */
  vector * v1 = create();  
  vector * v2 = create_vtr(3);  

  dump_vtr(v1);
  dump_vtr(v2);

  /* insert op tests */
  insert(v1, 1, 0);
  printf("insert(1,0) v1:\n");
  dump_vtr(v1);

  insert(v1, 3, 5);
  printf("insert(3,5) v1:\n");
  dump_vtr(v1);

  insert(v2, 1, 2);
  printf("insert(1,2) v2:\n");
  dump_vtr(v2);

  insert(v2, 2, 0);
  printf("insert(2,0) v2:\n");
  dump_vtr(v2);

  /* use copy constructor to make another vector */
  printf("result of create_cpy(v2):\n");
  vector * v3 = create_cpy(v2);
  dump_vtr(v3);

  /* remove/replace tests */
  printf("before remove_at(1) v1:\n");
  dump_vtr(v1);
  remove_at(v1, 1);
  printf("after remove_at(1) v1:\n");
  dump_vtr(v1);

  printf("before remove_elem(2) v2:\n");
  dump_vtr(v2);
  remove_elem(v2, 2);
  printf("after remove_elem(2) v2:\n");
  dump_vtr(v2);

  printf("before replace(1, 4) v2:\n");
  dump_vtr(v2);
  replace(v2, 4, 1);
  dump_vtr(v2);
  
  /* cleanup */
  destroy(v1);
  destroy(v2);
  destroy(v3);
}
