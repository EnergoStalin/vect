#ifndef SRC_VECT_VECT_H_
#define SRC_VECT_VECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vect vect;

vect *vect_init(size_t data_size, size_t capacity);
void vect_free(void *v);
void *vect_at(vect *v, size_t pos);
void *vect_push(vect *v);
void *vect_pop(vect *v);
void *vect_back(vect *v);
void vect_rem(vect *v, size_t pos);
void *vect_ins(vect *v, size_t pos);
size_t vect_size(vect *v);
size_t vect_capacity(vect *v);
size_t vect_data_size(vect *v);
void *vect_data(vect *v);

#define VECT_PUSH(V, VALUE) *(__typeof__(VALUE) *)vect_push(V) = VALUE
#define VECT_POP(V, VALUE) *(__typeof__(VALUE) *)vect_pop(V) = VALUE
#define VECT_INS(V, VALUE, POSITION) \
  *(__typeof__(VALUE) *)vect_ins(V, POSITION) = VALUE

#endif /* SRC_VECT_VECT_H_ */
