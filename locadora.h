#ifndef _H_LOCADORA
#define _H_LOCADORA

#define STR_BUF_SZ 10
#define FILM_BUF_SZ 5

typedef struct {
	char* title;
	char* director;
	int yearOfRelease;
	float rating;
	int qtde;
} film_t;

void addFilm(void);
void showFilms(void);
void explainFilm(void);
void printHeader(void);
int chooseOpt(void);
void handle(int opt);

void loadFilms();

#endif
