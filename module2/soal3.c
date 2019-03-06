#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#define max 7777

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    char scf[max];
    FILE *sc, *tg;

    char nfile[max] = "/home/rizk/Desktop/log.log";
    char ofile[max] = "/home/rizk/Desktop/sampah.txt";

    sc = fopen(ofile, "r");
    tg = fopen(nfile, "w");

    while(fgets(scf, max, sc) != NULL) fputs(scf, tg);
    fclose(sc); fclose(tg);
    sleep(2);
    remove(ofile);
    sleep(30);
  }
  
  exit(EXIT_SUCCESS);
}
