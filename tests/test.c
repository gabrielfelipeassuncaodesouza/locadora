#include "minunit.h"
#include "./../src/gutils.h"

MU_TEST(test_same_strings) {
  char *str1 = "string_test";
  char *str2 = "string_test";

  mu_check(strEq(str1, str2));
}

MU_TEST(test_same_strings_in_capslock) {
  char *str1 = "string_test";
  char *str2 = "STRING_TEST";

  mu_check(strEq(str1, str2));
}

MU_TEST_SUITE(test_compare_strings) {
  MU_RUN_TEST(test_same_strings);
  MU_RUN_SUITE(test_same_strings_in_capslock);
}

MU_TEST(test_different_strings) {
  char *str1 = "one_string";
  char* str2 = "another_string";

  mu_check(!strEq(str1, str2));
}

MU_TEST_SUITE(test_dimiss_different_strings) {
  MU_RUN_TEST(test_different_strings);
}

MU_TEST(test_two_movies_are_the_same) {
  movie_t m1 = { "Gabriel", "Felipe", 2023, 10.0, 10, 0 };
  movie_t m2 = { "Gabriel", "Felipe", 2023, 10.0, 10, 0 };

  mu_check(isEqual(&m1, &m2));
}

MU_TEST(test_two_movies_are_not_the_same) {
  movie_t m1 = { "Quentin", "Tarantino", 2023, 10.0, 10, 0 };
  movie_t m2 = { "Gabriel", "Felipe", 2023, 10.0, 10, 0 };

  mu_check(!isEqual(&m1, &m2));
}

MU_TEST_SUITE(test_compare_two_movies) {
  MU_RUN_TEST(test_two_movies_are_the_same);
  MU_RUN_TEST(test_two_movies_are_not_the_same);
}

int main() {
  MU_RUN_SUITE(test_compare_strings);
  MU_RUN_SUITE(test_dimiss_different_strings);
  MU_RUN_SUITE(test_compare_two_movies);

  MU_REPORT();

  return MU_EXIT_CODE;
}
