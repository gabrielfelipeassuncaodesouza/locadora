#include "locadora.h"
#include <stdio.h>
#include <stdlib.h>

void readInt(const char* msg, int* dest) {
	printf(msg);
	scanf("%d", dest);
	while(getchar() != '\n');	
}

void readFloat(const char* msg, float* dest) {
	printf(msg);
	scanf("%f", dest);
	while(getchar() != '\n');
}

char* readLine(const char* msg) {
	printf(msg);
	int bufsize = STR_BUF_SZ;
    char* buff = (char*)malloc(sizeof(char)*bufsize);

    if(!buff) {
        fprintf(stderr, "malloc error\n");
        return NULL;
    }

    int pos = 0;
    while(1) {
        int c = getchar();

        if(c == EOF || c == '\n') {
            buff[pos] = '\0';
			return buff;
        }

        buff[pos++] = c;

        if(pos >= bufsize) {
            bufsize += STR_BUF_SZ;
            buff = realloc(buff, bufsize);
            if(!buff) {
                fprintf(stderr, "malloc error\n");
                return NULL;
            }
        }
    }
}