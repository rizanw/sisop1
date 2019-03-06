#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child_id;
  int status;

  child_id = fork();

  if (child_id == 0) {
    char *argv[4] = {"mkdir", "-p", "anak", NULL};
    execv("/bin/mkdir", argv);
  } else {
    while ((wait(&status)) > 0);

    char *argv[4] = {"cp", "warisan.txt","anak" , NULL};
    execv("/bin/cp", argv);
  }
}
