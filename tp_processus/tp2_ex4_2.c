#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
        printf("Pipe In, pid=%d, ppid=%d", getpid(), getppid());

        // Close unused write end
        close(pipefd[0]);

        // Input from pipe = Standard output
        dup2(pipefd[1], 1);
        
        execl("/bin/grep", "grep", "|gayant|", "/usr/local/tmpIMA/printaccounting", NULL);
        
        close(pipefd[1]);
    } else if (pipe_in > 0) {
        pipe_out = fork();

        if (pipe_out == 0) {
            printf("Pipe Out, pid=%d, ppid=%d", getpid(), getppid());
        
            // Close unused read end
            close(pipefd[1]);

            // Output from pipe = Standard input
            dup2(pipefd[0], 0);

            // Output to /tmp/file
            int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            dup2(fd, 1);
            
            execl("/usr/bin/cut", "cut", "-f2", "-d|", NULL);
            
            close(pipefd[0]);
            close(fd);
        } else if (pipe_out > 0) {
            printf("Pere, pid=%d, ppid=%d", getpid(), getppid());

            close(pipefd[0]);
            close(pipefd[1]);
            
            int pid = wait(&status);
            printf("Fin fils %d, status=%d, return value=%d", pid, status, WEXITSTATUS(status));
            pid = wait(&status);
            printf("Fin fils %d, status=%d, return value=%d", pid, status, WEXITSTATUS(status));
        }
    }

    return 0;
}
