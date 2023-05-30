#include <check.h>
#include "s21_decimal.h"
#include <limits.h>

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

START_TEST(is_less_1)
{
    s21_decimal first = {
        {5, 0, 0, 65536}
    };
    s21_decimal second = {
        {61111, 0, 0, 327680}
    };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_2)
{
    s21_decimal first = {
        {62321, 0, 0, 327680}
    };
    s21_decimal second = {
        {5, 0, 0, 65536}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_3)
{
    s21_decimal first = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_4)
{
    s21_decimal first = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000010000000000000000}
    };
    s21_decimal second = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000100000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_5)
{
    s21_decimal first = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111110, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_6)
{
    s21_decimal first = {
        {0b11111110111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b00000000000000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_7)
{
    s21_decimal first = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000000000010000000000000000}
    };
    s21_decimal second = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000000100000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_8)
{
    s21_decimal first = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000100000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_9)
{
    s21_decimal first = {
        {UINT_MAX, UINT_MAX, UINT_MAX - 1, 0b00000000100000000000000000000000}
    };
    s21_decimal second = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000100000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 1);
}
END_TEST

START_TEST(is_less_10)
{
    s21_decimal first = {
        {UINT_MAX, UINT_MAX,        0, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000100000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_11)
{
    s21_decimal first = {
        {1,               0,        0, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {UINT_MAX, UINT_MAX, UINT_MAX, 0b00000000100000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
}
END_TEST

START_TEST(is_less_12)
{
    s21_decimal first = {
        {1, 1, 0, 0b00000000000000000000000000000000}
    };
    s21_decimal second = {
        {1, 1, 0, 0b00000000100000000000000000000000}
    };

    ck_assert(s21_is_less(first, second) == 0);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// START_TEST(is_less_0) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 255;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 256;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);

// // printf("\n\n");
// //   for(int i = 0; i < 4; ++i)
// //     printf("%u ", val1.bits[i]);
// // printf("\n");
// //   for(int i = 0; i < 4; ++i)
// //     printf("%u ", val2.bits[i]);
// // printf("\n\n");

//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 11);
//   setScale(&val2, 10);
//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_8) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   setBit(&val1, 83);
//   setBit(&val2, 127);
//   setScale(&val1, 12);
//   setScale(&val2, 11);

//   printf("first:\n");
//   for(int i = 0; i < 4; ++i)
//     printf("%u ", val1.bits[i]);
//   printf("\nsecond:\n");
//   for(int i = 0; i < 4; ++i)
//     printf("%u ", val2.bits[i]);
//   printf("\n");

//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_9) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   setBit(&val1, 83);
//   setBit(&val2, 83);
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_10) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   setBit(&val1, 83);
//   setScale(&val1, 10);
//   setScale(&val2, 10);
//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_11) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   setBit(&val1, 83);
//   ck_assert_int_eq(1, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_less_12) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   ck_assert_int_eq(0, s21_is_less(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_0) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 255;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 256;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 11);
//   setScale(&val2, 10);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(1, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   ck_assert_int_eq(1, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_8) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_0) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 255;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 256;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 11);
//   setScale(&val2, 10);
//   ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_or_equal_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_0) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 255;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 256;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 256;
//   ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 11);
//   setScale(&val2, 10);
//   ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_less_or_equal_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127);
//   setBit(&val2, 127);
//   ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_0) {
//   s21_decimal val1 = {{0, 0, 0, 0}};
//   s21_decimal val2 = {{0, 0, 0, 0}};
//   setBit(&val2, 127);
//   ck_assert_int_eq(1, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val2, 3);
//   ck_assert_int_eq(0, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val2, 127);
//   setBit(&val1, 33);
//   setBit(&val2, 33);
//   ck_assert_int_eq(0, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 3);
//   ck_assert_int_eq(1, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 4);
//   ck_assert_int_eq(0, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setScale(&val1, 3);
//   setScale(&val2, 3);
//   ck_assert_int_eq(1, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 4);
//   setScale(&val1, 3);
//   setScale(&val2, 3);
//   ck_assert_int_eq(0, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setScale(&val1, 3);
//   setScale(&val2, 2);
//   ck_assert_int_eq(1, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_equal_8) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(1, s21_is_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_0) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127);
//   ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_1) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val2, 3);
//   ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_2) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val2, 127);
//   setBit(&val1, 33);
//   setBit(&val2, 33);
//   ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_3) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 3);
//   ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 4);
//   ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setScale(&val1, 3);
//   setScale(&val2, 3);
//   ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 3);
//   setBit(&val2, 4);
//   setScale(&val1, 3);
//   setScale(&val2, 3);
//   ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setScale(&val1, 3);
//   setScale(&val2, 2);
//   ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
// }
// END_TEST

// START_TEST(is_not_equal_8) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
// }
// END_TEST

Suite *suite_comparisons(void) {
  Suite *s = suite_create("comparisons");
  TCase *tc = tcase_create("comparisons");

//   tcase_add_test(tc, is_less_0);
//   tcase_add_test(tc, is_less_1);
//   tcase_add_test(tc, is_less_2);
//   tcase_add_test(tc, is_less_3);
//   tcase_add_test(tc, is_less_4);
//   tcase_add_test(tc, is_less_5);
//   tcase_add_test(tc, is_less_6);
//   tcase_add_test(tc, is_less_7);
//   tcase_add_test(tc, is_less_8);
//   tcase_add_test(tc, is_less_9);
//   tcase_add_test(tc, is_less_10);
//   tcase_add_test(tc, is_less_11);
//   tcase_add_test(tc, is_less_12);

//   tcase_add_test(tc, is_greater_0);
//   tcase_add_test(tc, is_greater_1);
//   tcase_add_test(tc, is_greater_2);
//   tcase_add_test(tc, is_greater_3);
//   tcase_add_test(tc, is_greater_4);
//   tcase_add_test(tc, is_greater_5);
//   tcase_add_test(tc, is_greater_6);
//   tcase_add_test(tc, is_greater_7);
//   tcase_add_test(tc, is_greater_8);

  
//   tcase_add_test(tc, is_greater_or_equal_0);
//   tcase_add_test(tc, is_greater_or_equal_1);
//   tcase_add_test(tc, is_greater_or_equal_2);
//   tcase_add_test(tc, is_greater_or_equal_3);
//   tcase_add_test(tc, is_greater_or_equal_4);
//   tcase_add_test(tc, is_greater_or_equal_5);
//   tcase_add_test(tc, is_greater_or_equal_6);
//   tcase_add_test(tc, is_greater_or_equal_7);

//    tcase_add_test(tc, is_less_or_equal_0);  // s21_is_less_or_equal
//   tcase_add_test(tc, is_less_or_equal_1);
//   tcase_add_test(tc, is_less_or_equal_2);
//   tcase_add_test(tc, is_less_or_equal_3);
//   tcase_add_test(tc, is_less_or_equal_4);
//   tcase_add_test(tc, is_less_or_equal_5);
//   tcase_add_test(tc, is_less_or_equal_6);
//   tcase_add_test(tc, is_less_or_equal_7);
//   tcase_add_test(tc, is_equal_0);  // s21_is_equal
//   tcase_add_test(tc, is_equal_1);
//   tcase_add_test(tc, is_equal_2);
//   tcase_add_test(tc, is_equal_3);
//   tcase_add_test(tc, is_equal_4);
//   tcase_add_test(tc, is_equal_5);
//   tcase_add_test(tc, is_equal_6);
//   tcase_add_test(tc, is_equal_7);
//   tcase_add_test(tc, is_equal_8);
//   tcase_add_test(tc, is_not_equal_0);  // s21_is_not_equal
//   tcase_add_test(tc, is_not_equal_1);
//   tcase_add_test(tc, is_not_equal_2);
//   tcase_add_test(tc, is_not_equal_3);
//   tcase_add_test(tc, is_not_equal_4);
//   tcase_add_test(tc, is_not_equal_5);
//   tcase_add_test(tc, is_not_equal_6);
//   tcase_add_test(tc, is_not_equal_7);
//   tcase_add_test(tc, is_not_equal_8);
  


  ///////////////////////////////////////////////////

  tcase_add_test(tc, is_equal_same_numbers);
  tcase_add_test(tc, is_equal_different_numbers);

  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);
  tcase_add_test(tc, is_less_9);
  tcase_add_test(tc, is_less_10);
  tcase_add_test(tc, is_less_11);
  tcase_add_test(tc, is_less_12);

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
  
    return 0;
}