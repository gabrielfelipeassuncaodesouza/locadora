#ifndef _H_GUTILS
#define _H_GUTILS

#include "globconst.h"

void readline(const char* msg, char* dest);
void readchar(const char* msg, char* dest);
void readint(const char* msg, int* dest);
void readdouble(const char* msg, double* dest);
void aloca(movie_t* m);
int isEqual(movie_t* m1, movie_t* m2);
void pause(const char* msg);
void clearscr();

#endif