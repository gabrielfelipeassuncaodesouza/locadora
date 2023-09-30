#include "actions.h"
#include "gutils.h"
#include "globconst.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

movie_t* getMovie(state_t* s) {
  if(s->totalMovies == 0) {
    printError("\n\tErro: nenhum filme cadastrado!\n\n");
    return NULL;
  }

  movie_t* ret = NULL;

  char name[MAX_STR];
  char director[MAX_STR];

  int choice;
  do {
    clearscr();
    readint("\n\tDeseja pesquisar por:(1) nome, diretor(2) ou nome E diretor(3)? ", &choice);
  } while(choice < 1 || choice > 3);

  if(choice == 1 || choice == 3)
    readline("\n\tDigite o nome do filme: ", name);

  if(choice == 2 || choice == 3)
    readline("\n\tDigite o nome do diretor: ", director);

  for(int i = 0; i < s->totalMovies; i++) {
    int comp = (choice == 1) ? strEq(name, s->movies[i].title) : (choice == 2) ? strEq(director, s->movies[i].director) : (strEq(name, s->movies[i].title) && strEq(director, s->movies[i].director));   

    if(comp) {
      ret = &(s->movies[i]);
      break;
    }
  }

  return ret;
}

void registerMovie(state_t* s) {
    if(s->totalMovies ==  MAX_MOVIES) {
      printError("\n\tAlcançou o limite máximo de filmes\n");
      return;
    }

    movie_t f;
    aloca(&f);

    clearscr();
    printf("\n\t--- Cadastro de Filme ---\n\n");

    readline("\tDigite o nome do filme: ", f.title);
    readline("\tDigite o nome do diretor: ", f.director);
    readint("\tDigite o ano de lançamento: ", &f.yearOfRelease);
    readdouble("\tDigite a avaliação: ", &f.rating);
    readint("\tDigite a quantidade de cópias: ", &f.qtde);
    f.rent = 0;

    s->movies[s->totalMovies++] = f;

    printSucess("\n\tFilme cadastrado com sucesso!\n\n");
    s->dirty = true;
}

void searchMovie(state_t *s) {
  movie_t* ret = getMovie(s);

  if(ret == NULL) {
    printError("\n\tFilme não encontrado\n\n");
    return;
  }    

  printf("\n\tTítulo: %s\n", ret->title);
  printf("\tDiretor: %s\n", ret->director);
  printf("\tAno de Lançamento: %d\n", ret->yearOfRelease);
  printf("\tClassificação: %.2lf\n", ret->rating);
  printf("\tQuantidade em estoque: %d\n", ret->qtde);
  printf("\tCópias alugadas: %d\n", ret->rent);

  int choice;
  printf("\n\tOpções disponíveis: \n\n");
  printf("\t1 - Alugar cópias do filme\n");
  printf("\t2 - Devolver cópias alugadas\n");
  printf("\t3 - Deletar o filme\n");
  printf("\toutro número - Não fazer nada\n");

  readint("\n\t$> ", &choice);

  if(choice == 1) {
    rentMovie(ret);
    s->dirty = true;
  }
  else if(choice == 2) {
    giveBack(ret);
    s->dirty = true;
  }
  else if(choice == 3) {
    if(!deleteMovie(s, ret)) {
      printError("\n\tFilme não encontrado\n\n");
    }
    else {
      printSucess("\n\tFilme deletado com sucesso!\n\n");
      s->dirty = true;
    }
  }
}

void rentMovie(movie_t* ret) {
  if(ret == NULL) {
    printError("\n\tError: referência de pointeiro inválida\n\n");
    return;
  }

  int qtde;
  readint("\n\tDigite a quantidade de cópias: ", &qtde);

  if(qtde > ret->qtde) {
    printError("\n\tErro: estoque insuficiente\n\n");
    return;
  }

  ret->qtde-=qtde;
  ret->rent+=qtde;
  printSucess("\n\tCópias alugadas com sucesso\n\n");
}

void giveBack(movie_t *ret) {
  if(ret == NULL) {
    printError("\n\tError: Invalid reference to film\n\n");
    return;
  }

  int qtde;
  readint("\n\tDigite quantas cópias quer devolver: ", &qtde);

  if(qtde > ret->rent) {
    printError("\n\tErro: você não alugou essa quantidade de filmes\n\n");
    return;
  }

  ret->qtde+=qtde;
  ret->rent-=qtde;
  printSucess("\n\tCópias devolvidas com sucesso\n\n");
}

int deleteMovie(state_t* s, movie_t* ret) {
  if(ret == NULL) return 0;

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
  return 1;
}

void showMovies(state_t* s) {
  if (s->totalMovies == 0) {
    printError("\n\tNenhum filme cadastrado :(\n\n");
    return;
  }

  printf("\n\t--- Lista de Filmes ---\n\n");

  for (int i = 0; i < s->totalMovies; i++) {
    printf("\t%d -- %s\n", i+1, s->movies[i].title);
  }
  putchar('\n');
  stop("\tPressione enter para continuar ...");
}

void saveMovies(state_t* s) {
  if(s->totalMovies == 0) {
    printError("\n\tNenhum filme cadastrado :(\n\n");
    return;
  }

  FILE *file = fopen(ARQUIVO, "w");
  if (file == NULL) {
    printError("\n\tErro ao salvar os filmes :(\n");
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
  printSucess("\n\tFilmes salvos com sucesso :D\n\n");
  s->dirty = false;
}

void loadMovies(state_t *s) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printError("\n\tErro ao carregar filmes :(\n");
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

void generateReceive(state_t* s) {
  if(s->totalMovies == 0) {
    printError("\n\tNenhum filme cadastrado :(\n\n");
    return;
  }

  printf("\n\t--RECIBO ALUGUEL DE FILMES--\n\n");

  int totalCopys = 0;
  double totalCost = 0.0;

  for(int i = 0; i < s->totalMovies; i++) {
    if(s->movies[i].rent > 0) {
      printf("\tNome do filme: %s\n", s->movies[i].title);
      printf("\tCópias alugadas: %d\n", s->movies[i].rent);
      totalCopys+=(s->movies[i].rent);
      totalCost+=(s->movies[i].rent * MOVIE_PRICE);
    } 
  }

  printf("\n\n\tTotal de cópias alugadas: %d\n", totalCopys);
  printf("\tTotal a pagar: R$ %.2lf\n\n", totalCost);

  stop("\tPressione enter para continuar ...");
}
