#include "actions.h"
#include "gutils.h"
#include "globconst.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t global;

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
    pause("Press enter to continue... ");
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
  pause("\tBem vindo à locadora :D. Pressione enter para continuar... ");
}

int main() {
  init();
  loadMovies(&global);
  int opt;

  printHeader();

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