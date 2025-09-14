#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum pipe_side
{
    LEFT,
    RIGHT
};

static pid_t exec_fork(char **argv, int fds[2], enum pipe_side side)
{
    pid_t pid = fork();
    if (pid != 0)
        return pid;
    int fd_to_replace = side == LEFT ? STDOUT_FILENO : STDIN_FILENO;
    int fd_pipe_end = side == LEFT ? fds[1] : fds[0];

    if (dup2(fd_pipe_end, fd_to_replace) == -1)
        errx(1, "dup2 failed");

    close(fds[0]);
    close(fds[1]);

    execvp(argv[0], argv);
    errx(1, "execvp failed side : %d", side);
    return 0;
}

int exec_pipe(char **argv_left, char **argv_right)
{
    int fds[2];
    if (pipe(fds) == -1)
        errx(1, "pipe failed");

    int pid_left = exec_fork(argv_left, fds, LEFT);
    int pid_right = exec_fork(argv_right, fds, RIGHT);

    close(fds[0]);
    close(fds[1]);

    int wstatus;
    waitpid(pid_left, &wstatus, 0);
    waitpid(pid_right, &wstatus, 0);

    return WEXITSTATUS(wstatus);
}
