#include "minunit.h"
#include "./../src/gutils.h"
#include "./../src/actions.h"

state_t test_state;

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

MU_TEST(test_delete_a_single_movie) {
  movie_t movie_to_delete = test_state.movies[0];
  movie_t firstfilm = test_state.movies[1];
  movie_t secondfilm = test_state.movies[2];

  int initial_total = test_state.totalMovies;
  int ret = deleteMovie(&test_state, &movie_to_delete);

  mu_check(ret == 1);
  mu_assert_int_eq(test_state.totalMovies, (initial_total - 1));
  
  mu_check(isEqual(&(test_state.movies[0]), &movie_to_delete));
  mu_check(isEqual(&(test_state.movies[1]), &firstfilm));
}

MU_TEST(test_delete_a_null_movie) {
  movie_t* n = NULL;
  int ret = deleteMovie(&test_state, n);

  mu_check(ret == 0);
}

MU_TEST_SUITE(test_delete_movies) {
  MU_RUN_TEST(test_delete_a_single_movie);
  MU_RUN_TEST(test_delete_a_null_movie);
}

int main() {
  test_state.totalMovies = 0;
  test_state.dirty = false;

  test_state.movies[0] = (movie_t){ "Gabriel", "Felipe", 2004, 10.0, 10, 0 };
  test_state.movies[1] = (movie_t){ "Quentin", "Tarantino", 1980, 10.0, 10, 0 };
  test_state.movies[2] = (movie_t){ "Mateus", "Malhagaes", 2001, 10.0, 10, 0 };

  MU_RUN_SUITE(test_compare_strings);
  MU_RUN_SUITE(test_dimiss_different_strings);
  MU_RUN_SUITE(test_compare_two_movies);
  MU_RUN_SUITE(test_delete_movies);

  MU_REPORT();

  return MU_EXIT_CODE;
}