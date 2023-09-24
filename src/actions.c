#include "actions.h"
#include "gutils.h"
#include "globconst.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

movie_t* getMovie(state_t* s) {
  if(s->totalMovies == 0) {
    printf("\nNo films on storage!\n\n");
    return NULL;
  }

  movie_t* ret = NULL;

  char name[MAX_STR];
  char director[MAX_STR];

  int choice;
  do {
    readint("Do you wanna search by name (1), director (2) or name AND director (3)? ", &choice);
  } while(choice < 1 || choice > 3);

  if(choice == 1 || choice == 3)
    readline("\nType the name of the film: ", name);

  if(choice == 2 || choice == 3)
    readline("\nType the name of the director: ", director);

  for(int i = 0; i < s->totalMovies; i++) {

    int comp = (choice == 1) ? strcmp(name, s->movies[i].title) : (choice == 2) ? strcmp(director, s->movies[i].director) : (strcmp(name, s->movies[i].title) || strcmp(director, s->movies[i].director));   

    if(comp == 0) {
      ret = &(s->movies[i]);
      break;
    }
  }

  return ret;
}

void registerMovie(state_t* s) {
    if(s->totalMovies ==  MAX_MOVIES) {
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

    s->movies[s->totalMovies++] = f;

    printf("\nFilm cadastred sucessfully!\n\n");
    s->dirty = true;
}

void searchMovie(state_t *s) {
  movie_t* ret = getMovie(s);

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

  int choice;
  printf("\nOptions avaliables: \n\n");
  printf("1 - Rent the movie\n");
  printf("2 - Give back the movie\n");
  printf("3 - Delete the movie\n");
  printf("NoneOfAbove - Do nothing\n");

  readint("\n$> ", &choice);

  if(choice == 1) {
    rentMovie(ret);
    s->dirty = true;
  }
  else if(choice == 2) {
    giveBack(ret);
    s->dirty = true;
  }
  else if(choice == 3) {
    deleteMovie(s, ret);
    s->dirty = true;
  }
}

void rentMovie(movie_t* ret) {
  if(ret == NULL) {
    printf("\nError: Invalid reference to film\n\n");
    return;
  }

  int qtde;
  readint("\nInsert the quantity of copys: ", &qtde);

  if(qtde > ret->qtde) {
    printf("\nError: Insuficient stock\n\n");
    return;
  }

  ret->qtde-=qtde;
  ret->rent+=qtde;
  printf("\nMovie has been rented sucessfully\n\n");
}

void giveBack(movie_t *ret) {
  if(ret == NULL) {
    printf("\nError: Invalid reference to film\n\n");
    return;
  }

  int qtde;
  readint("\nInsert the quantity of copys to give back: ", &qtde);

  if(qtde > ret->rent) {
    printf("\nError: You don't have rented this quantity of copys\n\n");
    return;
  }

  ret->qtde+=qtde;
  ret->rent-=qtde;
  printf("\nMovie has been gave back sucessfully\n\n");
}

void deleteMovie(state_t* s, movie_t* ret) {
  if(ret == NULL) {
    printf("\nNo film found\n\n");
    return;
  }

  int index = MAX_MOVIES;

  for(int i = 0; i < s->totalMovies; i++) {
    if(isEqual(&(s->movies[i]), ret)) {
      index = i;
      break;
    }
  }

  for(int i = index; i < MAX_MOVIES - 1; i++) {
    s->movies[i] = s->movies[i+1];
  }

  s->totalMovies--;
  printf("\nMovie deleted sucessfully\n\n");
}

void showMovies(state_t* s) {
  if (s->totalMovies == 0) {
    printf("\nNo films on storage!\n\n");
    return;
  }

  printf("\n--- Lista de Filmes ---\n\n");

  for (int i = 0; i < s->totalMovies; i++) {
    printf("%d -- %s\n", i+1, s->movies[i].title);
  }
  putchar('\n');
}

void saveMovies(state_t* s) {
  if(s->totalMovies == 0) {
    printf("\nNo film storaged\n\n");
    return;
  }

  FILE *file = fopen(ARQUIVO, "w");
  if (file == NULL) {
    printf("Erro ao salvar os filmes!\n");
    return;
  }

  fseek(file, 0, SEEK_SET);
  fprintf(file, "%d\n", s->totalMovies);
  fseek(file, 0, SEEK_END);

  for (int i = 0; i < s->totalMovies; i++) {
    fprintf(file, "{ \"%s\", \"%s\", %d, %.2lf, %d, %d }\n", 
        s->movies[i].title, 
        s->movies[i].director, 
        s->movies[i].yearOfRelease, 
        s->movies[i].rating, 
        s->movies[i].qtde,
        s->movies[i].rent);
    }

  fclose(file);
  printf("\nFilmes salvos com sucesso!\n\n");
  s->dirty = false;
}

void loadMovies(state_t *s) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Error when loading the movies\n");
        return;
    }

    int qtde;
    fscanf(file, "%d\n", &qtde);

    aloca(&(s->movies[s->totalMovies]));

    for(int i = 0; i < qtde; i++) {
      fscanf(file, "{ \"%[^\"]\", \"%[^\"]\", %d, %lf, %d, %d }\n", 
                  s->movies[s->totalMovies].title, 
                  s->movies[s->totalMovies].director, 
                  &(s->movies[s->totalMovies].yearOfRelease), 
                  &(s->movies[s->totalMovies].rating), 
                  &(s->movies[s->totalMovies].qtde),
                  &(s->movies[s->totalMovies].rent));

      aloca(&(s->movies[++(s->totalMovies)]));
    }

    fclose(file);
}
