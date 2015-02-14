/*
 * vector.c - the implementation of the functions in vector.h. This is a wrapper
 * on malloc(3) that emulates a subset of vector (dynamic array) functions. 
 *
 * Reference:
 *
 * http://stackoverflow.com/questions/7826163/whats-the-best-c-implementation-of-the-c-vector
 */
#include <stdio.h>    /* for printf */
#include <string.h>   /* for memcpy/memmove */
#include "vector.h"   /* the vector API definitions */

/* 
 * malloc(3) is different on different platforms, so we use preprocessor macros to
 * indicate which header file to use, for what. Reference:
 * http://sourceforge.net/p/predef/wiki/OperatingSystems/
 */
#ifdef __FreeBSD__
#include <malloc_np.h>
#endif

#ifdef __linux__
#include <malloc.h>
#endif

/* shiftdir's, used for resizing. */
#define LSHIFT  1
#define RSHIFT  -1

/* a "constructor" */
vector * create_vtr(size_t size) {
    vector * vtr = (vector *) malloc(sizeof(vector));
    if (vtr) {
        vtr->data = malloc(size * sizeof(int));
        vtr->size = size;
    }
    return vtr;
}

/* a no-args "constructor" */
vector * create() {
    return create_vtr(0);
}

/* a "copy constructor" */
vector * create_cpy(vector * vtr) {
    size_t s = vtr->size;    

    vector * cpy = create_vtr(s); 
    if (cpy) {
        memcpy(cpy->data, vtr->data, s * sizeof(int));
        cpy->size = s;
    }
    return cpy;
}

/* a "destructor" */
void destroy(vector * vtr) {
    free(vtr->data);
    free(vtr);
}

static size_t resize_vtr(vector * vtr, size_t size) {
    if (vtr) {
        int * d = realloc(vtr->data, size * sizeof(int));
        if (d) {
            vtr->data = d;
            vtr->size = size;
        }
        return vtr->size;
    }
    return 0;
}

/*
 * shift array from tail to position, or vice versa.
 * shiftdir indicates direction to shift elements.
 */
static void shift_data(vector * vtr, int pos, int shiftdir) {
    int i;
    if (shiftdir == RSHIFT) {
        for (i = (vtr->size - 1); i >= pos; i--) {
            vtr->data[i] = vtr->data[i - 1];
        }
    } else {
        for (i = pos + 1; i < (vtr->size); i++) {
            vtr->data[i - 1] = vtr->data[i];
        }
    }
}

/*
 * shift array done with memmove(3). We don't use memcpy(3)
 * because the memory overlaps, and the latter will clobber
 * things up when it needs to write to the same areas. 
 */
static void shift_data_mm(vector * vtr, int pos, int shiftdir) {
    /* get the pointer and move it forward by pos */
    int * dp = (vtr->data) + pos;      
    /* compute amount to move */
    size_t len = (vtr->size - (pos + 1)) * sizeof(int);

    if (shiftdir == RSHIFT) {
        memmove(dp + 1, dp, len);
    } else {
        memmove(dp, dp + 1, len);
    }
}

/* insert element at position */
void insert(vector * vtr, int elem, int pos) {
    int cur_s = vtr->size;

    /* check if we have space. If not, resize */
    if (cur_s - 1 < pos) {
        resize_vtr(vtr, pos + 1);
    } else { 
        resize_vtr(vtr, cur_s + 1);
    }

    /* insert new element at index pos. */
    shift_data_mm(vtr, pos, RSHIFT);
    vtr->data[pos] = elem;
}

/* remove element at position given */
int remove_at(vector * vtr, int pos) {
    if (pos >= vtr->size) {
      return -1;
    }

    shift_data_mm(vtr, pos, RSHIFT);
    resize_vtr(vtr, vtr->size - 1);    
    return 0;
}

/* replace element at position with one given */
int replace(vector * vtr, int elem, int pos) {
    if (vtr->size <= pos) {
        return -1;
    }

    vtr->data[pos] = elem;
    return 0;
}

size_t size_vtr(vector * vtr) {
  return vtr->size;
}

int * to_array(vector * vtr) {
  return vtr->data;
}

/* print vector data contents and address */
void dump_vtr(vector * vtr) {
    int i;
    printf("size: %zu \ndata:\n", vtr->size);
    for (i = 0; i < vtr->size; i++) {
      printf("%d ", vtr->data[i]);
    }
    printf("\n\n");
}
