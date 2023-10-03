
#include "globconst.h"
#include "gutils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strEq(char* str1, char* str2) {
  if(strlen(str1) != strlen(str2)) return 0;

  if(str1 == NULL || str2 == NULL) return 0;

  for(int i = 0; i < strlen(str1); i++) {
    if(tolower(str1[i]) != tolower(str2[i])) return 0;
  }

  return 1;
}

void readline(const char* msg, char* dest) {
  printf(msg);
  char* aux = (char*)malloc(sizeof(char)*MAX_STR);

  fgets(aux, MAX_STR, stdin);
  aux[strcspn(aux, "\n")] = '\0';
  aux = trim(aux);

  strcpy(dest, aux);
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

void libera(movie_t* m) {
  free(m->title);
  free(m->director);
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

char *ltrim(char *s) 
{     
    while(isspace(*s)) s++;     
    return s; 
}  

char *rtrim(char *s) 
{     
    char* back;
    int len = strlen(s);

    if(len == 0)
        return(s); 

    back = s + len;     
    while(isspace(*--back));     
    *(back+1) = '\0';     
    return s; 
}  

char *trim(char *s) 
{     
    return rtrim(ltrim(s));  
} 