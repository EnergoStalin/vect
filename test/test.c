#include <check.h>
#include <stdlib.h>

#include "../vect.h"

START_TEST(vect_1) {
  vect *d = vect_init(sizeof(double), 15);

  ck_assert_int_eq(15, vect_capacity(d));
  ck_assert_int_eq(sizeof(double), vect_data_size(d));
  ck_assert_int_eq(vect_size(d), 0);
  ck_assert_ptr_ne(vect_data(d), 0);

  vect_free(d);
}
END_TEST

START_TEST(vect_2) {
  vect *d = vect_init(sizeof(double), 300);

  ck_assert_int_eq(300, vect_capacity(d));
  ck_assert_int_eq(sizeof(double), vect_data_size(d));
  ck_assert_int_eq(vect_size(d), 0);

  VECT_PUSH(d, 5.0);
  ck_assert_uint_eq(vect_size(d), 1);
  ck_assert_int_eq(*(double *)vect_pop(d), 5);

  VECT_PUSH(d, 5.0);
  ck_assert_uint_eq(vect_size(d), 1);

  VECT_INS(d, 8.0, 0);
  ck_assert_uint_eq(vect_size(d), 2);
  ck_assert_double_eq(*(double *)vect_at(d, 0), 8);
  ck_assert_double_eq(*(double *)vect_at(d, 1), 0);
  ck_assert_double_eq(*(double *)vect_at(d, 2), 5);

  VECT_INS(d, 8.0, 0);
  ck_assert_int_eq(*(double *)vect_at(d, 3), 5);
  ck_assert_double_eq(*(double *)vect_back(d), 5);

  size_t prev = vect_size(d);
  vect_rem(d, 2);
  ck_assert_uint_eq(vect_size(d), prev - 1);

  vect_free(d);
}
END_TEST

START_TEST(vect_3) {
  vect *d = vect_init(sizeof(double), 15);

  vect_pop(d);

  vect_free(d);
}
END_TEST

START_TEST(vect_4) {
  vect *d = vect_init(sizeof(double), 1);

  VECT_INS(d, 6.0, 5);

  vect_free(d);
}
END_TEST

START_TEST(vect_5) {
  vect *d = vect_init(sizeof(double), 1);

  VECT_INS(d, 6.0, 0);
  VECT_INS(d, 6.0, 0);
  VECT_INS(d, 6.0, 0);
  VECT_INS(d, 6.0, 0);

  vect_free(d);
}
END_TEST

START_TEST(vect_6) {
  vect *d = vect_init(sizeof(double), 1);

  VECT_PUSH(d, 6.0);
  VECT_PUSH(d, 6.0);
  VECT_PUSH(d, 6.0);
  VECT_PUSH(d, 6.0);

  vect_free(d);
}
END_TEST

Suite *vect_suite() {
  Suite *s = suite_create("vect");

  TCase *tc = tcase_create("vect");
  tcase_add_test(tc, vect_1);
  tcase_add_test(tc, vect_2);
  tcase_add_exit_test(tc, vect_3, 1);
  tcase_add_exit_test(tc, vect_4, 1);
  tcase_add_test(tc, vect_5);
  tcase_add_test(tc, vect_6);
  suite_add_tcase(s, tc);

  return s;
}

int main() {
  SRunner *sr = srunner_create(vect_suite());

  // Should fork for correct fail checking
  // srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
