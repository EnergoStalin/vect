#include "vect.h"

void vect_err(const char *error) {
  fprintf(stderr, "%s\n", error);
  exit(1);
}

vect *vect_init(size_t data_size, size_t capacity) {
  vect *v = (vect *)malloc(sizeof(vect));
  if (v == NULL) vect_err("vect_init: allocation of vect failed.");
  if (capacity == 0) capacity = VECT_CAPACITY;
  v->data = malloc(data_size * capacity);
  if (v->data == NULL) vect_err("vect_init: allocation of vect data failed.");
  v->data_size = data_size;
  v->size = 0;
  v->capacity = capacity;
  return v;
}

void vect_free(void *v) {
  free(((vect *)v)->data);
  free(((vect *)v));
}

void vect_resize(vect *v) {
  v->capacity *= 2; /* double capacity */
  v->data = realloc(v->data, v->data_size * v->capacity);
  if (v->data == NULL) vect_err("vect_resize: resize failed.");
}

size_t vect_chk_bounds(vect *v, size_t pos) { return (pos < v->size); }

size_t vect_at(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_at: out of bounds.");
  return pos;
}

size_t vect_set(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_set: out of bounds.");
  return pos;
}

size_t vect_push(vect *v) {
  if (v->size == v->capacity) vect_resize(v);
  return v->size++;
}

size_t vect_pop(vect *v) {
  if (v->size == 0) vect_err("vect_pop: underflow.");
  return --v->size;
}

size_t vect_rem(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_rem: out of bounds.");
  char *dest = (char *)v->data + (v->data_size * pos);
  char *src = dest + v->data_size;
  size_t num_bytes = v->data_size * (v->size - pos - 1);
  memmove(dest, src, num_bytes);
  v->size--;
  return pos;
}

size_t vect_ins(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_ins: out of bounds.");
  char *src = (char *)v->data + (v->data_size * pos);
  char *dest = src + v->data_size;
  size_t num_bytes = v->data_size * (v->size - pos);
  memmove(dest, src, num_bytes);
  v->size++;
  return pos;
}
