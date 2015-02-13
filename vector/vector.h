/*
 * vector.h - A header file for a minimal vector library. This is meant to
 * demonstrate various C concepts, not be a serious vector library.
 */
#include <stdlib.h>   /* for size_t */ 

/*
 * a container for the data in the vector 
 */
typedef struct int_vtr {
    size_t size;    /* size of vector */
    int * data;     /* data in vector - ints */
} vector;

/*
 * Functions for creating and destryoing vectors.
 */
struct int_vtr * create_vtr(size_t size);
vector * create();
vector * create_cpy(vector * vtr);
void destroy(vector * vtr);

/*
 * Functions for adding, removing, and modifying things in a vector.
 */
void insert(vector * vtr, int elem, int pos);
void remove_elem(vector * vtr, int elem);
int remove_at(vector * vtr, int pos);
int replace(vector * vtr, int elem, int pos);

/*
 * Functions for utility
 */
size_t size_vtr(vector * vtr);
int * to_array(vector * vtr);
void dump_vtr(vector * vtr);
