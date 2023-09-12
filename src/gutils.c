#include "globals.h"

#include <stdio.h>
#include <string.h>

void readline(const char* msg, char* dest) {
  printf(msg);
  fgets(dest, MAX_STR, stdin);
  dest[strcspn(dest, "\n")] = '\0';
}

void readint(const char* msg, int* dest) {
  printf(msg);
  scanf("%d", dest);
  while(getchar() != '\n');
}

void readdouble(const char* msg, double* dest) {
  printf(msg);
  scanf("%lf", dest);
  while(getchar() != '\n');
}