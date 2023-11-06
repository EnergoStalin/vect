#ifndef SRC_VECT_VECT_H_
#define SRC_VECT_VECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECT_CAPACITY 256

typedef struct vect vect;

void vect_err(const char *error);
vect *vect_init(size_t data_size, size_t capacity);
void vect_free(void *v);
void vect_resize(vect *v);
size_t vect_chk_bounds(vect *v, size_t pos);
void *vect_at(vect *v, size_t pos);
void *vect_push(vect *v);
void *vect_pop(vect *v);
void *vect_top(vect *v);
void vect_rem(vect *v, size_t pos);
void *vect_ins(vect *v, size_t pos);
size_t vect_size(vect *v);
size_t vect_capacity(vect *v);
size_t vect_data_size(vect *v);

#endif /* SRC_VECT_VECT_H_ */
