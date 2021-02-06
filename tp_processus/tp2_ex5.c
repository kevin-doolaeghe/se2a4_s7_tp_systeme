#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define SEUIL 10

void ecoute(int pipefd[]) {
    // Close unused read end
    close(pipefd[1]);

    int nb = 0;
    do {
        scanf("%d", &nb);
        printf("%d\n", nb);
    } while (nb != 0);
    
    close(pipefd[0]);
}

void envoi(int pipefd[]) {
    // Close unused write end
    close(pipefd[0]);

    printf("Entrer des entiers :\n");
    int nb = 0;
    do {
        scanf("%d", &nb);
        if (nb % 2 == 0 && nb > SEUIL) {
            write (pipefd[1], &nb, sizeof(int));
        }
    } while (nb != 0);
    
    close(pipefd[1]);
}

int main() {
    int pipe_in;
    int pipe_out;
    int status;

    int pipefd[2];
    pipe(pipefd);

    pipe_in = fork();

    /*
     * <0 --> fork failed
     * =0 --> child process
     * >0 --> parent process
     */
    if (pipe_in == 0) {
        printf("Pipe In, pid=%d, ppid=%d\n", getpid(), getppid());
        
        envoi(pipefd);
    } else if (pipe_in > 0) {
        pipe_out = fork();

        if (pipe_out == 0) {
            printf("Pipe Out, pid=%d, ppid=%d\n", getpid(), getppid());
            
            ecoute(pipefd);
        } else if (pipe_out > 0) {
            printf("Pere, pid=%d, ppid=%d\n", getpid(), getppid());

            close(pipefd[0]);
            close(pipefd[1]);
            
            int pid = wait(&status);
            printf("Fin fils %d, status=%d, return value=%d\n", pid, status, WEXITSTATUS(status));
            pid = wait(&status);
            printf("Fin fils %d, status=%d, return value=%d\n", pid, status, WEXITSTATUS(status));
        }
    }

    return 0;
}
