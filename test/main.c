#include "main.h"

#include <stdlib.h>

int main() {
  SRunner *sr = srunner_create(double_suite());

  srunner_add_suite(sr, int_suite());
  srunner_add_suite(sr, char_suite());

  // Should fork for correct error checking work
  // srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
