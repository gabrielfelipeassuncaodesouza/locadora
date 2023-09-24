#include "actions.h"
#include "gutils.h"
#include "globconst.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t global;

void generateReceive(state_t* s) {
  printf("\n--RECIBO ALUGUEL DE FILMES--\n\n");

  int totalCopys = 0;
  double totalCost = 0.0;

  for(int i = 0; i < s->totalMovies; i++) {
    if(s->movies[i].rent > 0) {
      printf("Movie's name: %s\n", s->movies[i].title);
      printf("Cópias alugadas: %d\n", s->movies[i].rent);
      totalCopys+=(s->movies[i].rent);
      totalCost+=(s->movies[i].rent * MOVIE_PRICE);
    } 
  }

  printf("\n\nTotal de cópias alugadas: %d\n", totalCopys);
  printf("Total a pagar: R$ %.2lf\n\n", totalCost);
}

void quit() {
  if(!global.dirty) return;

  char choice;
  readchar("\nDeseja salvar as alterações [y/n]? ", &choice);

  if(tolower(choice) == 'y') {
    saveMovies(&global);
  }
}

void handle(int opt) {
  switch(opt) {
    case 1:
      registerMovie(&global);
      break;
    case 2:
      showMovies(&global);
      break;
    case 3:
      searchMovie(&global);
      break;
    case 4:
      generateReceive(&global);
      break;
    case 5:
      saveMovies(&global);
      break;
    case EXIT_CONST:
      quit();
      break;
    default:
      printf("Invalid option!\n");
  }

  if(opt != EXIT_CONST)
    pause("Press any key to continue... ");
}

void init() {
  global.totalMovies = 0;
  global.dirty = false;
}

int main() {
  init();
  loadMovies(&global);
  int opt;

  do {
    clearscr();

    printf("\nLocadora de Filmes\n");
    printf("\n1 - Register movie\n");
    printf("2 - See movies registered\n");
    printf("3 - Search a movie\n");
    printf("4 - Generate receive\n");
    printf("5 - Save Films\n");
    printf("6 - Quit\n");
        
    readint("\n$> ", &opt);

    handle(opt); 

  } while(opt != EXIT_CONST);

  return 0;
}
