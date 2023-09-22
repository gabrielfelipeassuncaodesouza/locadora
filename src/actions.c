#include "gutils.h"
#include "globconst.h"

#include <stdbool.h>
#include <stdio.h>

void cadastrarFilme(state_t* s) {
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

void searchMovie() {
  movie_t* ret = getMovie();

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

void deleteMovie(state_t* s) {
  movie_t* ret = getMovie();

  if(ret == NULL) {
    printf("\nNo film found\n\n");
    return;
  }
  printf("film found\n");

  int index = -1;

  for(int i = 0; i < s->totalMovies; i++) {
    if(isEqual(&(s->movies[i]), ret)) {
      index = i;
      break;
    }
  }

  printf("film found\n");

  for(int i = index; i < MAX_MOVIES - 1; i++) {
    s->movies[i] = s->movies[i+1];
  }

  s->totalMovies--;
  printf("\nMovie deleted sucessfully\n\n");

  s->dirty = true;
}

void rentMovie(state_t* s) {
  movie_t* ret = getMovie();

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

  s->dirty = true;
}