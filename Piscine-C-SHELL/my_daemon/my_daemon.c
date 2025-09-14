#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int nb_signals = 0;
static int current_generation = 0;

void handler(int signum)
{
    pid_t spid;
    switch (signum)
    {
    case (SIGUSR1):
        nb_signals++;
        printf("Received %d signals.\n", nb_signals);
        fflush(stdout);
        break;
    case (SIGUSR2):
        nb_signals++;
        printf("Current generation: %d\n", current_generation);
        fflush(stdout);
        break;
    case (SIGTERM):
        current_generation++;
        nb_signals = 0;
        spid = fork();
        if (spid < 0)
            exit(1);
        else if (spid > 0)
            exit(0);
        break;
    case (SIGINT):
        nb_signals++;
        exit(0);
        break;
    default:
        break;
    }
}

int main(void)
{
    pid_t pid = fork();
    if (pid < 0)
        exit(1);
    else if (pid > 0)
        exit(0);
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigemptyset(&sa.sa_mask) < 0)
    {
        exit(0);
    }
    if (sigaction(SIGINT, &sa, NULL) < 0)
    {
        exit(0);
    }
    if (sigaction(SIGUSR1, &sa, NULL) < 0)
    {
        exit(0);
    }
    if (sigaction(SIGUSR2, &sa, NULL) < 0)
    {
        exit(0);
    }
    if (sigaction(SIGTERM, &sa, NULL) < 0)
    {
        exit(0);
    }
    while (1)
    {
        continue;
    }
}
