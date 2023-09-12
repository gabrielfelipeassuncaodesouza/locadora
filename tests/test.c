#include "minunit.h"

MU_TEST(test1) {
  mu_check(5 == 7);
}

MU_TEST_SUITE(test) {
  MU_RUN_TEST(test1);
}

int main() {
  MU_RUN_SUITE(test);
  MU_REPORT();

  return MU_EXIT_CODE;
}
