#include <check.h>
#include <stdlib.h>

#include "../common.h"
#include "main.h"

START_TEST(vect_1) {
  vect_double *d = vect_init_double(15);

  ck_assert_int_eq(15, d->capacity);
  ck_assert_int_eq(sizeof(double), d->data_size);
  ck_assert_int_eq(d->size, 0);

  vect_free(d);
}
END_TEST

START_TEST(vect_2) {
  vect_double *d = vect_init_double(15);

  ck_assert_int_eq(15, d->capacity);
  ck_assert_int_eq(sizeof(double), d->data_size);
  ck_assert_int_eq(d->size, 0);

  vect_push_double(d, 5);
  ck_assert_uint_eq(d->size, 1);
  ck_assert_double_eq(vect_pop_double(d), 5);
  vect_push_double(d, 5);
  ck_assert_uint_eq(d->size, 1);

  vect_ins_double(d, 0, 8);
  ck_assert_uint_eq(d->size, 2);
  ck_assert_double_eq(vect_at_double(d, 0), 8);
  ck_assert_double_eq(vect_at_double(d, 1), 5);
  vect_ins_double(d, 0, 8);
  ck_assert_double_eq(vect_at_double(d, 2), 5);

  size_t prev = d->capacity;
  vect_resize((vect *)d);
  ck_assert_uint_eq(d->capacity, prev * 2);

  vect_set_double(d, 2, 8);
  ck_assert_double_eq(vect_at_double(d, 2), 8);

  prev = d->size;
  vect_rem_double(d, 2);
  ck_assert_uint_eq(d->size, prev - 1);

  vect_free(d);
}
END_TEST

START_TEST(vect_3) {
  vect_int *d = vect_init_int(15);

  vect_pop_double(d);

  vect_free(d);
}
END_TEST

Suite *double_suite() {
  Suite *s = suite_create("vect_double");

  TCase *tc = tcase_create("double");
  tcase_add_test(tc, vect_1);
  tcase_add_test(tc, vect_2);
  tcase_add_exit_test(tc, vect_3, 1);
  suite_add_tcase(s, tc);

  return s;
}
