#include <check.h>

#include "s21_decimal.h"

int main() {
  int nf;
  SRunner *sr;
  //converters
  // sr = srunner_create(suite_from_int_to_decimal());
  // sr = srunner_create(suite_from_decimal_to_int());
  sr = srunner_create(test_from_float_to_decimal());


  // srunner_add_suite(sr, test_from_float_to_decimal());
  // srunner_add_suite(sr,suite_from_decimal_to_float());
  // srunner_add_suite(sr,suite_from_decimal_to_int());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
