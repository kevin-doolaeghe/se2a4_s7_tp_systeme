#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fils1;
    int fils2;
    int status;

    fils1 = fork();

    /*
     * <0 --> fork failed
     * =0 --> child process
     * >0 --> parent process
     */
    if (fils1 == 0) {
        sleep(2);
        printf("Fils1, pid=%d,ppid=%d", getpid(), getppid());
        return 42;
    } else if (fils1 > 0) {
        fils2 = fork();
        if (fils2 == 0) {
            sleep(2);
            printf("Fils2, pid=%d,ppid=%d", getpid(), getppid());
            return 24;
        } else if (fils2 > 0) {
            printf("Pere, pid=%d,ppid=%d", getpid(), getppid());
            int pid = wait(&status);
            printf("Fin fils n°%d, status=%d, return val=%d", pid, status, WEXITSTATUS(status));
            pid = wait(&status);
            printf("Fin fils n°%d, status=%d, return val=%d", pid, status, WEXITSTATUS(status));

        }
    }

    return 0;
}
