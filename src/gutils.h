#ifndef _H_GUTILS
#define _H_GUTILS

#include "globconst.h"

void readline(const char* msg, char* dest);
void readchar(const char* msg, char* dest);
void readint(const char* msg, int* dest);
void readdouble(const char* msg, double* dest);

void aloca(movie_t* m);
int isEqual(movie_t* m1, movie_t* m2);
int strEq(char* str1, char* str2);
void stop(const char* msg);
void clearscr();
void printError(const char* msg);
void printSucess(const char* msg);

#endif