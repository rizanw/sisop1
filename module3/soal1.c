#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t tid1, tid2;
int status;

struct args{
	char *file1;
	char *file2;
	char *file3;
};

void *salin(char *filein, char *fileout);
void *salin1(void *ptr);
void *salin2(void *ptr);

int main(){
	int th1, th2;
	char *file = "baca.txt";
	char *file1 = "salin1.txt";
	char *file2 = "salin2.txt";

	struct args *cmd = (struct args *)malloc(sizeof(struct args));
    cmd->file1 = file;
    cmd->file2 = file1;
    cmd->file3 = file2;

	th1 = pthread_create(&tid1, NULL, salin1, (void*) cmd);
	if(th1){
		fprintf(stderr, "Error - pthread_create() return code: %d\n", th1);
		exit(EXIT_FAILURE);
	}
	th2 = pthread_create(&tid2, NULL, salin2, (void*) cmd);
	if(th2){
		fprintf(stderr, "Error - pthread_create() return code %d\n", th1);
		exit(EXIT_FAILURE);
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// printf("pthread_create() for th1 returns: %d\n", th1);
	// printf("pthread_create() for th2 returns: %d\n", th2);

	exit(EXIT_SUCCESS);
	return 0;
}

void *salin1(void *ptr){
	status = 0;
	salin(((struct args*)ptr)->file1, ((struct args*)ptr)->file2);
	status = 1;
	return 0;
}

void *salin2(void *ptr){
	while(status != 1) return 0;
	salin(((struct args*)ptr)->file2, ((struct args*)ptr)->file3);
	return 0;
}

void *salin(char *filein, char *fileout){
	char txt;

	FILE *src, *dst;

	printf("%s\n", filein);

	src = fopen(filein, "r");
	if (src == NULL){
        printf("File input: %s does not exists \n", filein);
        return 0;
    }

	dst = fopen(fileout, "w");
    if (dst == NULL){
        printf("File output: %s does not exists \n", fileout);
        return 0;
    }

	while ((txt = fgetc(src)) != EOF)
		fputc(txt, dst);

    fclose(src);
    fclose(dst);

    return 0;
}