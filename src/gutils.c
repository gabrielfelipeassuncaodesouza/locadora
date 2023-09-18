#include "globconst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readline(const char* msg, char* dest) {
  printf(msg);
  fgets(dest, MAX_STR, stdin);
  dest[strcspn(dest, "\n")] = '\0';
}

void readchar(const char* msg, char* dest) {
  printf(msg);
  scanf("%c", dest);
  while(getchar() != '\n');
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

void aloca(movie_t* m) {
  m->title = (char*)malloc(sizeof(char)*MAX_STR);
  m->director = (char*)malloc(sizeof(char)*MAX_STR);
}

int isEqual(movie_t* m1, movie_t* m2) {
  return strcmp(m1->title, m2->title) == 0 &&
          strcmp(m1->director, m2->director) == 0 &&
          m1->yearOfRelease == m2->yearOfRelease &&
          m1->rating == m2->rating &&
          m1->qtde == m2->qtde &&
          m1->rent == m2->rent;
}

void clearscr() {
  printf("\x1b[2J");
  printf("\x1b[H");
}

void pause(const char* msg) {
  printf(msg);
  getchar();
}