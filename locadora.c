#include "gutils.h"
#include "locadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

film_t films[FILM_BUF_SZ];
int totalFilms = 0;

void loadFilms() {
	FILE *f = fopen("films.txt", "r");
	if(f == NULL) {
		fprintf(stderr, "Error when open films\n");
		exit(EXIT_FAILURE);
	}

	int qtde;
	char* film = (char*)malloc(sizeof(char)*1000);
	fscanf(f, "%d\n", &qtde);
	fscanf(f, "{ '%s' }", film);

	printf("We have %d films on storage\n", qtde);
	printf("The %s is the first film\n", film);
}
 
void addFilm(void) {
	film_t new;

	new.title = readLine("\nType the title of the film: ");
	new.director = readLine("Type the name of the director: ");
	readInt("Type the year of release: ", &new.yearOfRelease);
	readFloat("Type the rating: ", &new.rating);
	readInt("Type the quantity of copys: ", &new.qtde);

	films[totalFilms++] = new;
	
	printf("\nAdded sucessfully\n\n");
}

void showFilms(void) {
	if(!totalFilms) {
		fprintf(stderr, "\nNo films on storage!\n\n");
		return;
	}

	printf("\n**** LIST OF FILMS ****\n\n");
	
	for(int i = 0; i < totalFilms; i++) {
		printf("%d - %s\n", i+1, films[i].title);
	}
	printf("\n***********************\n\n");
}

void explainFilm(void) {
	if(!totalFilms) {
		fprintf(stderr, "\nNo films on storage\n\n");
		return;
	}

	showFilms();

	int index;
	readInt("Type the index of the film: \n$> ", &index);
	index--;

	if(index < 0 || index >= totalFilms) {
		fprintf(stderr, "\nNo film in this index\n\n");
	}
	else {
		printf("\n**** FILM DATA ****\n\n");

		printf("Title: %s\n", films[index].title);
		printf("Director: %s\n", films[index].director);
		printf("Year of release: %d\n", films[index].yearOfRelease);
		printf("Rating: %.1f\n", films[index].rating);
		printf("Quantity avaliable: %d\n\n", films[index].qtde);
	}
}

void printHeader(void) {
	printf("\x1b[2J"); //clear the screen
	printf("\x1b[H"); //pos the cursor to the left-top corner

	printf("******************\n");
	printf("**** LOCADORA ****\n");
	printf("******************\n\n");
}

int chooseOpt(void) {

	const char* msg = "1 - Add film\n2 - Show all films\n3 - Show a film's data\n4 - Quit\n\n$> ";
	
	int ret;
	readInt(msg, &ret);
	return ret;
}

void handle(int opt) {
	switch(opt) {
		case 1:
			addFilm();
			break;
		case 2:
			showFilms();
			break;
		case 3:
			explainFilm();
			break;
		case 4:
			break;
		default:
			printf("Invalid option!\n");
			break;
	}
}

int main(void) {
	//int opt;
	loadFilms();
	//printHeader();

	//do {
	//	opt = chooseOpt();
	//	handle(opt);	

	//} while(opt != 4);

	return 0;
}