#ifndef _H_GLOBALS
#define _H_GLOBALS

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

#endif