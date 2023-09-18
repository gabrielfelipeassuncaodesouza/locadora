#include "gutils.h"
#include "globals.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

movie_t movies[MAX_MOVIES];
int totalFilmes = 0;

int dirty = false;

void aloca(movie_t* m) {
  m->title = (char*)malloc(sizeof(char)*MAX_STR);
  m->director = (char*)malloc(sizeof(char)*MAX_STR);
}

void cadastrarFilme() {
    if(totalFilmes ==  MAX_MOVIES) {
      printf("Got limit of films\n");
      return;
    }

    movie_t f;
    aloca(&f);

    printf("\n--- Cadastro de Filme ---\n\n");

    readline("Enter the name of the movie: ", f.title);
    readline("Enter the name of the director: ", f.director);
    readint("Enter the year of release: ", &f.yearOfRelease);
    readdouble("Enter the rating: ", &f.rating);
    readint("Enter the quantity of copys in storage: ", &f.qtde);
    f.rent = 0;

    //TODO: verifiy if the

    movies[totalFilmes++] = f;

    printf("\nFilm cadastred sucessfully!\n\n");
    dirty = true;
}

int isEqual(movie_t m1, movie_t m2) {
  return strcmp(m1.title, m2.title) == 0 &&
          strcmp(m1.director, m2.director) == 0 &&
          m1.yearOfRelease == m2.yearOfRelease &&
          m1.rating == m2.rating &&
          m1.qtde == m2.qtde;
}

movie_t* getMovie(char* name) {
  for(int i = 0; i < totalFilmes; i++) {
    if(strcmp(name, movies[i].title) == 0) {
      return &movies[i];
    }
  }

  return NULL;
}

void searchMovie() {
    if(totalFilmes == 0) {
      printf("\nNo films on storage!\n\n");
      return;
    }

    char name[MAX_STR];
    readline("\nType the name of the film: ", name);
    movie_t* ret = getMovie(name);

    if(ret == NULL) {
      printf("\nNo film found\n\n");
      return;
    }    

    printf("\nTítulo: %s\n", ret->title);
    printf("Diretor: %s\n", ret->director);
    printf("Ano de Lançamento: %d\n", ret->yearOfRelease);
    printf("Classificação: %.2lf\n", ret->rating);
    printf("Quantidade em estoque: %d\n", ret->qtde);
    printf("Cópias alugadas: %d\n", ret->rent);

    putchar('\n');
}

void showMovies() {
    if (totalFilmes == 0) {
        printf("\nNo films on storage!\n\n");
        return;
    }

    printf("\n--- Lista de Filmes ---\n\n");

    for (int i = 0; i < totalFilmes; i++) {
      printf("%d -- %s\n", i+1, movies[i].title);
    }
    putchar('\n');
}

void salvarFilmes() {
    if(totalFilmes == 0) {
      printf("\nNo film storaged\n\n");
      return;
    }

    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro ao salvar os filmes!\n");
        return;
    }

    for (int i = 0; i < totalFilmes; i++) {
        fprintf(file, "{ \"%s\", \"%s\", %d, %.2lf, %d, %d }\n", 
                movies[i].title, 
                movies[i].director, 
                movies[i].yearOfRelease, 
                movies[i].rating, 
                movies[i].qtde,
                movies[i].rent);
    }

    fclose(file);
    printf("\nFilmes salvos com sucesso!\n\n");
}

void carregarFilmes() {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Error when loading the movies\n");
        return;
    }

    movie_t m;
    aloca(&m);

    while(fscanf(file, "{ \"%[^\"]\", \"%[^\"]\", %d, %lf, %d, %d }\n", 
                  m.title, 
                  m.director, 
                  &m.yearOfRelease, 
                  &m.rating, 
                  &m.qtde,
                  &m.rent) != EOF) {

        movies[totalFilmes++] = m;
    }

    fclose(file);
}

void clearscr() {
  printf("\x1b[2J");
  printf("\x1b[H");
}

void pause(const char* msg) {
  printf(msg);
  getchar();
}

void rentMovie() {
  if(totalFilmes == 0) {
    printf("No films on storage!\n");
    return;
  }

  char name[MAX_STR];
  readline("\nType the name of the film: ", name);
  movie_t* ret = getMovie(name);

  if(ret == NULL) {
    printf("\nNo film found\n\n");
    return;
  }

  int qtde;
  readint("Insert the quantity of copys: ", &qtde);

  if(qtde > ret->qtde) {
    printf("\nError: Insuficient stock\n\n");
    return;
  }

  ret->qtde-=qtde;
  ret->rent+=qtde;
  printf("\nMovie has been rented sucessfully\n\n");

  dirty = true;
}

void generateReceive() {
  printf("\n--RECIBO ALUGUEL DE FILMES--\n\n");

  int totalCopys = 0;
  double totalCost = 0.0;

  for(int i = 0; i < totalFilmes; i++) {
    if(movies[i].rent > 0) {
      printf("Movie's name: %s\n", movies[i].title);
      printf("Cópias alugadas: %d\n", movies[i].rent);
      totalCopys+=movies[i].rent;
      totalCost+=(movies[i].rent * MOVIE_PRICE);
    } 
  }

  printf("\n\nTotal de cópias alugadas: %d\n", totalCopys);
  printf("Total a pagar: R$ %.2lf\n\n", totalCost);
}

void quit() {
  if(!dirty) return;

  char choice;
  readchar("\nDeseja salvar as alterações [y/n]? ", &choice);

  if(tolower(choice) == 'y') {
    salvarFilmes();
  }
}

void handle(int opt) {
  switch(opt) {
    case 1:
      cadastrarFilme();
      break;
    case 2:
      showMovies();
      break;
    case 3:
      searchMovie();
      break;
    case 4:
      rentMovie();
      break;
    case 5:
      generateReceive();
      break;
    case 6:
      salvarFilmes();
      break;
    case 7:
      quit();
      break;
    default:
      printf("Invalid option!\n");
  }

  if(opt != 7)
    pause("Press any key to continue... ");
}

int main() {
    carregarFilmes();
    int opt;

    do {
        clearscr();

        printf("\nLocadora de Filmes\n");
        printf("\n1 - Cadastrar Filme\n");
        printf("2 - See movies Cadastrados\n");
        printf("3 - Search a movie\n");
        printf("4 - Rent a movie\n");
        printf("5 - Generate receive\n");
        printf("6 - Save Films\n");
        printf("7 - Quit\n");
        
        readint("\n$> ", &opt);

        handle(opt); 

    } while(opt != 7);

    return 0;
}
