#include "gutils.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

movie_t movies[MAX_MOVIES];
int totalFilmes = 0;

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

    movies[totalFilmes++] = f;
}

int isEqual(movie_t m1, movie_t m2) {
  return strcmp(m1.title, m2.title) == 0 &&
          strcmp(m1.director, m2.director) == 0 &&
          m1.yearOfRelease == m2.yearOfRelease &&
          m1.rating == m2.rating &&
          m1.qtde == m2.qtde;
}

movie_t* getMovie(movie_t movies[], char* name) {
  for(int i = 0; i < totalFilmes; i++) {
    if(strcmp(name, movies[i].title) == 0) {
      return &movies[i];
    }
  }

  return NULL;
}

void searchMovie() {
    if(totalFilmes == 0) {
      printf("No films on storage!\n");
      return;
    }

    char name[MAX_STR];
    readline("\nType the name of the film: ", name);
    movie_t* ret = getMovie(movies, name);

    if(ret == NULL) {
      printf("\nNo film found\n\n");
      return;
    }    

    printf("\nTítulo: %s\n", ret->title);
    printf("Diretor: %s\n", ret->director);
    printf("Ano de Lançamento: %d\n", ret->yearOfRelease);
    printf("Classificação: %.2lf\n", ret->rating);
    printf("Quantidade em estoque: %d\n", ret->qtde);

    putchar('\n');
}

void showMovies() {
    printf("\n--- Lista de Filmes ---\n\n");

    if (totalFilmes == 0) {
        printf("\nNo films on storage!\n\n");
        return;
    }

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
        fprintf(file, "{ \"%s\", \"%s\", %d, %.2lf, %d }\n", 
                movies[i].title, 
                movies[i].director, 
                movies[i].yearOfRelease, 
                movies[i].rating, 
                movies[i].qtde);
    }

    fclose(file);
    printf("\nFilmes salvos com sucesso!\n\n");
}

void carregarFilmes() {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Error when loading the movies\n");
        return; // Se o arquivo não existir ou não puder ser aberto, simplesmente retorna
    }

    //TODO: check if limits of film are respected;

    movie_t m;
    aloca(&m);

    while(fscanf(file, "{ \"%[^\"]\", \"%[^\"]\", %d, %lf, %d }\n", 
                  m.title, 
                  m.director, 
                  &m.yearOfRelease, 
                  &m.rating, 
                  &m.qtde) != EOF) {

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
  movie_t* ret = getMovie(movies, name);

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
  printf("\nMovie has been rented sucessfully\n\n");
}

void generateReceive() {

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
      salvarFilmes();
      break;
    case 6:
      generateReceive();
      break;
    case 7:
      return;
    default:
      printf("Invalid option!\n");
  }

  pause("Press any key to continue... ");
}

int main() {
    carregarFilmes();
    int opt;

    do {
        clearscr();

        printf("\nLocadora de Filmes\n");
        printf("\n1 - Cadastrar Filme\n");
        printf("2 - Ver Filmes Cadastrados\n");
        printf("3 - Pesquisar um filme\n");
        printf("4 - Rent a movie\n");
        printf("5 - Salvar Filmes \n");
        printf("6 - Quit\n");
        
        readint("\n$> ", &opt);

        handle(opt); 

    } while(opt != 6);

    return 0;
}
