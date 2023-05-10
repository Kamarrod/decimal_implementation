#include <check.h>
#include "s21_decimal.h"

START_TEST(is_equal_same_numbers) {
    s21_decimal first = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
    s21_decimal second = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345

    ck_assert(s21_is_equal(first, second) == 1);
}
END_TEST

START_TEST(is_equal_different_numbers) {
    s21_decimal first = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
    s21_decimal second = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; //  -1.2345

    ck_assert(s21_is_equal(first, second) == 0);
}
END_TEST

START_TEST(is_less_different_signs) {
    s21_decimal first = {
      {12344, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
    s21_decimal second = {
      {12345, 0, 0, 0b10000000000001000000000000000000}}; //  -1.2345

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_same_signs_same_numbers) {
    s21_decimal first = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345
    s21_decimal second = {
      {12345, 0, 0, 0b00000000000001000000000000000000}}; //  1.2345

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_same_signs_different_values) {
    s21_decimal first = {
        {  123, 0, 0, 0b00000000000001000000000000000000}   //  1.2344
    };
    s21_decimal second = {
        {12345, 0, 0, 0b00000000000001000000000000000000} //  1.2345
      };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_same_values) {
    s21_decimal first = {
        { 0, 0, 0, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        { 0, 0, 0, 0b00000000000000000000000000000000} 
      };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_same_values_different_powers) {
    s21_decimal first = {
        { 123, 0, 0, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 123, 0, 0, 0b00000000000100000000000000000000}
      };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_all_numbers_filled_1) {
    s21_decimal first = {
        { 111, 111, 110, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_all_numbers_filled_2) {
    s21_decimal first = {
        { 111, 111, 112, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_not_equal_same_numbers) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_not_equal(first, second) == 0);
}
END_TEST

START_TEST(is_not_equal_different_signs) {
    s21_decimal first = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_not_equal(first, second) == 1);
}
END_TEST

START_TEST(is_not_equal_different_values_1) {
    s21_decimal first = {
        { 111, 111, 000, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_not_equal(first, second) == 1);
}
END_TEST

START_TEST(is_not_equal_different_values_2) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 000, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_not_equal(first, second) == 1);
}
END_TEST




START_TEST(is_less_or_equal_equalNumbers) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_less_or_equal_first_less_1) {
    s21_decimal first = {
        { 111, 111, 000, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_less_or_equal_first_less_2) {
    s21_decimal first = {
        { 111, 111, 112, 0b10000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_less_or_equal_first_less_3) {
    s21_decimal first = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_less_or_equal_first_less_4) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 121, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_less_or_equal_first_greater_1) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 0);
}
END_TEST

START_TEST(is_less_or_equal_first_greater_2) {
    s21_decimal first = {
        { 111, 111, 112, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_less_or_equal(first, second) == 0);
}
END_TEST

START_TEST(is_greater_first_greater_1) {
    s21_decimal first = {
        { 111, 111, 112, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 1);
}
END_TEST

START_TEST(is_greater_first_greater_2) {
    s21_decimal first = {
        { 111, 112, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 1);
}
END_TEST

START_TEST(is_greater_first_greater_3) {
    s21_decimal first = {
        { 112, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 1);
}
END_TEST

START_TEST(is_greater_first_greater_4) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 1);
}
END_TEST

START_TEST(is_greater_first_greater_5) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 999999, 0b10000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 1);
}
END_TEST

START_TEST(is_greater_first_less_1) {
    s21_decimal first = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 0);
}
END_TEST

START_TEST(is_greater_first_less_2) {
    s21_decimal first = {
        { 111, 111, 110, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 0);
}
END_TEST

START_TEST(is_greater_first_less_3) {
    s21_decimal first = {
        { 110, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 0);
}
END_TEST

START_TEST(is_greater_equal_numbers) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater(first, second) == 0);
}
END_TEST




START_TEST(is_greater_or_equal_first_greater_1) {
    s21_decimal first = {
        { 111, 111, 112, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_greater_or_equal_first_greater_2) {
    s21_decimal first = {
        { 111, 112, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_greater_or_equal_first_greater_3) {
    s21_decimal first = {
        { 112, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_greater_or_equal_first_greater_4) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_greater_or_equal_first_greater_5) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 999999, 0b10000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST

START_TEST(is_greater_or_equal_first_less_1) {
    s21_decimal first = {
        { 111, 111, 111, 0b10000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 0);
}
END_TEST

START_TEST(is_greater_or_equal_first_less_2) {
    s21_decimal first = {
        { 111, 111, 110, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 0);
}
END_TEST

START_TEST(is_greater_or_equal_first_less_3) {
    s21_decimal first = {
        { 110, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 0);
}
END_TEST

START_TEST(is_greater_or_equal_equal_numbers) {
    s21_decimal first = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
    };
    s21_decimal second = {
        { 111, 111, 111, 0b00000000000001000000000000000000}
      };
    ck_assert(s21_is_greater_or_equal(first, second) == 1);
}
END_TEST


Suite *suite_comparisons(void) {
  Suite *s = suite_create("comparisons");
  TCase *tc = tcase_create("comparisons");

  tcase_add_test(tc, is_equal_same_numbers);
  tcase_add_test(tc, is_equal_different_numbers);

  tcase_add_test(tc, is_less_different_signs);
  tcase_add_test(tc, is_less_same_signs_same_numbers);
  tcase_add_test(tc, is_less_same_signs_different_values);
  tcase_add_test(tc, is_less_same_values);
  tcase_add_test(tc, is_less_same_values_different_powers);
  tcase_add_test(tc, is_less_all_numbers_filled_1);
  tcase_add_test(tc, is_less_all_numbers_filled_2);
  
  tcase_add_test(tc, is_less_or_equal_equalNumbers);
  tcase_add_test(tc, is_less_or_equal_first_greater_1);
  tcase_add_test(tc, is_less_or_equal_first_greater_2);
  tcase_add_test(tc, is_less_or_equal_first_less_1);
  tcase_add_test(tc, is_less_or_equal_first_less_2);
  tcase_add_test(tc, is_less_or_equal_first_less_3);
  tcase_add_test(tc, is_less_or_equal_first_less_4);

  tcase_add_test(tc, is_greater_first_greater_1);
  tcase_add_test(tc, is_greater_first_greater_2);
  tcase_add_test(tc, is_greater_first_greater_3);
  tcase_add_test(tc, is_greater_first_greater_4);
  tcase_add_test(tc, is_greater_first_greater_5);
  tcase_add_test(tc, is_greater_first_less_1);
  tcase_add_test(tc, is_greater_first_less_2);
  tcase_add_test(tc, is_greater_first_less_3);
  tcase_add_test(tc, is_greater_equal_numbers);

  tcase_add_test(tc, is_greater_or_equal_first_greater_1);
  tcase_add_test(tc, is_greater_or_equal_first_greater_2);
  tcase_add_test(tc, is_greater_or_equal_first_greater_3);
  tcase_add_test(tc, is_greater_or_equal_first_greater_4);
  tcase_add_test(tc, is_greater_or_equal_first_greater_5);
  tcase_add_test(tc, is_greater_or_equal_first_less_1);
  tcase_add_test(tc, is_greater_or_equal_first_less_2);
  tcase_add_test(tc, is_greater_or_equal_first_less_3);
  tcase_add_test(tc, is_greater_or_equal_equal_numbers);


  tcase_add_test(tc, is_not_equal_same_numbers);
  tcase_add_test(tc, is_not_equal_different_signs);
  tcase_add_test(tc, is_not_equal_different_values_1);
  tcase_add_test(tc, is_not_equal_different_values_2);

  suite_add_tcase(s, tc);
  return s;
}

int main(int argc, char** argv)
{
    int nf;
    SRunner *sr;
    sr = srunner_create(suite_comparisons());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
  
    return nf == 0 ? 0 : 1;
}