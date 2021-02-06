#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 128

int main() {
    int fils;
    int status;

    char nom_fichier[NAME_SIZE];
    printf("Enter file name : ");
    fgets(nom_fichier, NAME_SIZE, stdin);
    nom_fichier[strlen(nom_fichier) - 1] = '\0';

    fils = fork();

    /*
     * <0 --> fork failed
     * =0 --> child process
     * >0 --> parent process
     */
    if (fils == 0) {
        printf("Fils, pid=%d, ppid=%d", getpid(), getppid());
        int fd = open("/tmp/result", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        execl("/usr/bin/wc", "wc", "-l", nom_fichier, NULL);
    } else if (fils > 0) {
        int pid = wait(&status);
        printf("Fin fils %d, status=%d, return value=%d", pid, status, WEXITSTATUS(status));
    }

    return 0;
}
