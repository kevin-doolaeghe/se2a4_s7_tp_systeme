#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

int main() {
    int pipe_in;
    int pipe_out;
    int status;
    char buf;

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

        // Close unused write end
        close(pipefd[0]);

        char buffer[BUF_SIZE + 1];
        fgets(buffer, BUF_SIZE, 0);
        write (pipefd[1], &buf, 1);
        
        close(pipefd[1]);
    } else if (pipe_in > 0) {
        pipe_out = fork();

        if (pipe_out == 0) {
            printf("Pipe Out, pid=%d, ppid=%d\n", getpid(), getppid());
        
            // Close unused read end
            close(pipefd[1]);

            char buffer[BUF_SIZE + 1];
            read(pipefd[0], buffer, BUF_SIZE);

            printf("Chaine reçue : %s\n", buffer);
            
            char pair[BUF_SIZE];
            int seuil = 0;
            printf("Entrer le seuil : ");
            seuil = fgetc(0);

            int i = 0;
            int j = 0;
            while (i < BUF_SIZE && buffer[i] != 48) {
                if (buffer[i] % 2 == 0 && buffer[i] > seuil) pair[j++] = buffer[i++];
            }
            pair[i] = 0;

            for (i = 0; i < j; i++) {
                printf("Id %d, value %d\n", i, pair[i]);
            }

            close(pipefd[0]);
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
