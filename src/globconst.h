#ifndef _H_GLOBALS
#define _H_GLOBALS

#include <stdbool.h>

#define ARQUIVO "filmes.txt"

#define MAX_STR 100
#define MAX_MOVIES 5
#define MOVIE_PRICE 10

typedef struct {
    char* title;
    char* director;
    int yearOfRelease;
    double rating;
    int qtde;
    int rent;
} movie_t;

typedef struct {
  movie_t movies[MAX_MOVIES];
  int totalMovies;
  bool dirty;
} state_t;

movie_t* getMovie();

#define EXIT_CONST 8

#endif