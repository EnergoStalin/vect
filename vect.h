#ifndef SRC_VECT_VECT_H_
#define SRC_VECT_VECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECT_CAPACITY 256

typedef struct {
  size_t size;
  size_t capacity;
  size_t data_size;
  void *data;
} vect;

void vect_err(const char *error);
vect *vect_init(size_t data_size, size_t capacity);
void vect_free(void *v);
void vect_resize(vect *v);
size_t vect_chk_bounds(vect *v, size_t pos);
size_t vect_at(vect *v, size_t pos);
size_t vect_set(vect *v, size_t pos);
size_t vect_push(vect *v);
size_t vect_pop(vect *v);
size_t vect_rem(vect *v, size_t pos);
size_t vect_ins(vect *v, size_t pos);

#define VECT_DECLARE_TYPE(TYPE) VECT_DECLARE_NAME(TYPE, TYPE)
#define VECT_DECLARE_NAME(TYPE, NAME)                           \
  typedef struct {                                              \
    size_t size;                                                \
    size_t capacity;                                            \
    size_t data_size;                                           \
    TYPE *data;                                                 \
  } vect_##NAME;                                                \
  vect_##NAME *vect_init_##NAME(size_t capacity);               \
  TYPE *vect_ptr_##NAME(vect_##NAME *v, size_t pos);            \
  TYPE vect_at_##NAME(vect_##NAME *v, size_t pos);              \
  void vect_push_##NAME(vect_##NAME *v, TYPE value);            \
  void vect_set_##NAME(vect_##NAME *v, size_t pos, TYPE value); \
  TYPE vect_pop_##NAME(vect_##NAME *v);                         \
  void vect_rem_##NAME(vect_##NAME *v, size_t pos);             \
  void vect_ins_##NAME(vect_##NAME *v, size_t pos, TYPE value);

#define VECT_DECLARE_NESTED_PTR_FREE_FOR_NAME(NAME) \
  void vect_free_inner_ptrs_##NAME(vect_##NAME *v);

#define VECT_GENERATE_TYPE(TYPE) VECT_GENERATE_NAME(TYPE, TYPE)
#define VECT_GENERATE_NAME(TYPE, NAME)                           \
  vect_##NAME *vect_init_##NAME(size_t capacity) {               \
    return (vect_##NAME *)vect_init(sizeof(TYPE), capacity);     \
  }                                                              \
  TYPE *vect_ptr_##NAME(vect_##NAME *v, size_t pos) {            \
    return v->data + vect_at((vect *)v, pos);                    \
  }                                                              \
  TYPE vect_at_##NAME(vect_##NAME *v, size_t pos) {              \
    size_t idx = vect_at((vect *)v, pos);                        \
    return v->data[idx];                                         \
  }                                                              \
  void vect_push_##NAME(vect_##NAME *v, TYPE value) {            \
    size_t idx = vect_push((vect *)v);                           \
    v->data[idx] = value;                                        \
  }                                                              \
  void vect_set_##NAME(vect_##NAME *v, size_t pos, TYPE value) { \
    size_t idx = vect_set((vect *)v, pos);                       \
    v->data[idx] = value;                                        \
  }                                                              \
  TYPE vect_pop_##NAME(vect_##NAME *v) {                         \
    size_t idx = vect_pop((vect *)v);                            \
    return v->data[idx];                                         \
  }                                                              \
  void vect_rem_##NAME(vect_##NAME *v, size_t pos) {             \
    vect_rem((vect *)v, pos);                                    \
  }                                                              \
  void vect_ins_##NAME(vect_##NAME *v, size_t pos, TYPE value) { \
    size_t idx = vect_ins((vect *)v, pos);                       \
    v->data[idx] = value;                                        \
  }

#define VECT_GENERATE_NESTED_PTR_FREE_FOR_NAME(NAME, FREEFUNC) \
  void vect_free_inner_ptrs_##NAME(vect_##NAME *v) {           \
    for (size_t i = 0; i < v->size; i++) {                     \
      FREEFUNC(vect_at_##NAME(v, i));                          \
    }                                                          \
    vect_free(v);                                              \
  }

#include "common.h"

#endif /* SRC_VECT_VECT_H_ */
