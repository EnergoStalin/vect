#include "vect.h"

#define VECT_CAPACITY 256

struct vect {
  size_t size;
  size_t capacity;
  size_t data_size;
  void *data;
};

void vect_err(const char *error) {
  fprintf(stderr, "%s\n", error);
  exit(1);
}

void vect_resize(vect *v) {
  v->capacity *= 2; /* double capacity */
  v->data = realloc(v->data, v->data_size * v->capacity);
  if (v->data == NULL) vect_err("vect_resize: resize failed.");
}

size_t vect_chk_bounds(vect *v, size_t pos) { return (pos <= v->size); }

vect *vect_init(size_t data_size, size_t capacity) {
  vect *v = (vect *)malloc(sizeof(vect));
  if (v == NULL) vect_err("vect_init: allocation of vect failed.");
  if (capacity == 0) capacity = VECT_CAPACITY;
  v->data = calloc(capacity, data_size);
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

void *vect_at(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_at: out of bounds.");
  return ((char *)v->data + (pos * v->data_size));
}

void *vect_push(vect *v) {
  if (v->size == v->capacity) vect_resize(v);
  return ((char *)v->data + (v->size++ * v->data_size));
}

void *vect_pop(vect *v) {
  if (v->size == 0) vect_err("vect_pop: underflow.");
  return ((char *)v->data + (--v->size * v->data_size));
}

void *vect_back(vect *v) {
  return ((char *)v->data + ((v->size - 1) * v->data_size));
}

void vect_rem(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos)) vect_err("vect_rem: out of bounds.");
  char *dest = (char *)v->data + (v->data_size * (pos - 1));
  char *src = dest + v->data_size;
  size_t num_bytes = v->data_size * (v->size - pos);
  memmove(dest, src, num_bytes);
  v->size--;
}

void *vect_ins(vect *v, size_t pos) {
  if (!vect_chk_bounds((vect *)v, pos))
    vect_err("vect_ins: out of bounds.");
  else if (v->size == v->capacity)
    vect_resize(v);

  char *src = (char *)v->data + (v->data_size * pos);
  char *dest = src + v->data_size;
  size_t num_bytes = v->data_size * (v->size - pos);
  memmove(dest, src, num_bytes);

  v->size++;

  return vect_at(v, pos);
}

size_t vect_size(vect *v) { return v->size; }
size_t vect_capacity(vect *v) { return v->capacity; }
size_t vect_data_size(vect *v) { return v->data_size; }
void *vect_data(vect *v) { return v->data; }
