#include <check.h>

#include "s21_decimal.h"

int main() {
  int nf;
  SRunner *sr;
  sr = srunner_create(suite_add());
  // srunner_add_suite(test_from_float_to_decimal());
  // srunner_add_suite(suite_from_decimal_to_float());
  // srunner_add_suite(suite_from_int_to_decimal());
  // srunner_add_suite(suite_from_decimal_to_int());
  // srunner_add_suite(suite_add());
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
