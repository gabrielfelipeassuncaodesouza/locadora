#include "actions.h"
#include "gutils.h"
#include "globconst.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

state_t global;

void quit() {
  if(!global.dirty) return;

  char choice;
  readchar("\n\tDeseja salvar as alterações [y/n]? ", &choice);

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
      printError("\n\tOpção inválida!\n");
  }

  if(opt != EXIT_CONST)
    usleep(1000000);
}

void init() {
  global.totalMovies = 0;
  global.dirty = false;
}

void printHeader() {
  clearscr();

  printf("\n\n");
  printf("\t __                                  __                                                       \n");
  printf("\t/\\ \\                                /\\ \\                                                  \n");
  printf("\t\\ \\ \\        ___     ___     __     \\_\\ \\    ___   _ __    __                           \n");
  printf("\t \\ \\ \\  __  / __`\\  /'___\\ /'__`\\   /'_` \\  / __`\\/\\`'__\\/'__`\\                    \n");
  printf("\t  \\ \\ \\L\\ \\/\\ \\L\\ \\/\\ \\__//\\ \\L\\.\\_/\\ \\L\\ \\/\\ \\L\\ \\ \\ \\//\\ \\L\\.\\_\n"); 
  printf("\t   \\ \\____/\\ \\____/\\ \\____\\ \\__/.\\_\\ \\___,_\\ \\____/\\ \\_\\  \\__/.\\_\\         \n");
  printf("\t    \\/___/  \\/___/  \\/____/\\/__/\\/_/\\/__,_ /\\/___/  \\/_/ \\/__/\\/_/                  \n");
                                                                    
  printf("\n\n");
  stop("\tBem vindo à locadora :D. Pressione enter para continuar... ");
}

int main() {
  init();
  loadMovies(&global);
  int opt;

  printHeader();

  do {
    clearscr();

    printf("\n\tLocadora de Filmes\n");
    printf("\n\t1 - Adicionar filme\n");
    printf("\t2 - Ver filmes disponíveis\n");
    printf("\t3 - Pesquisar um filme\n");
    printf("\t4 - Gerar recibo\n");
    printf("\t5 - Salvar alterações\n");
    printf("\t6 - Sair\n");
        
    readint("\n\t$> ", &opt);

    handle(opt); 

  } while(opt != EXIT_CONST);

  return 0;
}