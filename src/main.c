#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "filmes.txt"

#define MAX_STR 100
#define MAX_MOVIES 5

typedef struct {
    char* title;
    char* director;
    int yearOfRelease;
    double rating;
    int qtde;
} movie_t;

movie_t movies[MAX_MOVIES];

int totalFilmes = 0;

void readline(const char* msg, char* dest) {
  printf(msg);
  fgets(dest, MAX_STR, stdin);
  dest[strcspn(dest, "\n")] = '\0';
}

void readint(const char* msg, int* dest) {
  printf(msg);
  scanf("%d", dest);
  while(getchar() != '\n');
}

void readdouble(const char* msg, double* dest) {
  printf(msg);
  scanf("%lf", dest);
  while(getchar() != '\n');
}

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

    printf("\n--- Cadastro de Filme ---\n");

    readline("Enter the name of the movie: ", f.title);
    readline("Enter the name of the director: ", f.director);
    readint("Enter the year of release: ", &f.yearOfRelease);
    readdouble("Enter the rating: ", &f.rating);
    readint("Enter the quantity of copys in storage: ", &f.qtde);

    movies[totalFilmes++] = f;
}

void exibirFilme() {
    int index;
    readint("Type the index of the film: ", &index);

    if(totalFilmes == 0) {
      printf("No films on storage!\n");
    }

    if(index < 0 || index >= totalFilmes) {
      printf("Invalid index!\n");
      return;
    }

    movie_t f = movies[index];
    printf("\nTítulo: %s\n", f.title);
    printf("Diretor: %s\n", f.director);
    printf("Ano de Lançamento: %d\n", f.yearOfRelease);
    printf("Classificação: %.2lf\n", f.rating);
    printf("Quantidade em estoque: %d\n", f.qtde);
}

void mostrarFilmes() {
    printf("\n--- Lista de Filmes ---\n\n");

    if (totalFilmes == 0) {
        printf("No films on storage!\n");
        return;
    }

    for (int i = 0; i < totalFilmes; i++) {
      printf("%s\n", movies[i].title);
    }
}

void salvarFilmes() {
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
    printf("Filmes salvos com sucesso!\n");
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

void handle(int opt) {
  switch(opt) {
    case 1:
      cadastrarFilme();
      break;
    case 2:
      mostrarFilmes();
      break;
    case 3:
      exibirFilme();
      break;
    case 4:
      salvarFilmes();
      break;
    case 5:
      break;
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
        printf("3 - Ver Dados de um filme\n");
        printf("4 - Salvar Filmes \n");
        printf("5 - Quit\n");
        
        readint("\n$> ", &opt);

        handle(opt); 

    } while(opt != 5);

    return 0;
}
