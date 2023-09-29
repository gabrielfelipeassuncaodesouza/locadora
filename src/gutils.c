#include "globconst.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strEq(char* str1, char* str2) {
  if(strlen(str1) != strlen(str2)) return 0;

  for(int i = 0; i < strlen(str1); i++) {
    if(tolower(str1[i]) != tolower(str2[i])) return 0;
  }

  return 1;
}

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
  return strEq(m1->title, m2->title) &&
          strEq(m1->director, m2->director) &&
          m1->yearOfRelease == m2->yearOfRelease &&
          m1->rating == m2->rating &&
          m1->qtde == m2->qtde &&
          m1->rent == m2->rent;
}

void clearscr() {
  printf("\x1b[2J");
  printf("\x1b[H");
}

void stop(const char* msg) {
  printf(msg);
  getchar();
}

void printError(const char* msg) {
  printf("\x1b[31m%s\x1b[m", msg);
}

void printSucess(const char* msg) {
  printf("\x1b[32m%s\x1b[m", msg);
}