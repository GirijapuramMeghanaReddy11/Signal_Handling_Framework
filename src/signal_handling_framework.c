#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t usr1_received = 0;
volatile sig_atomic_t usr2_received = 0;
volatile sig_atomic_t terminate = 0;
volatile sig_atomic_t child_finished = 0;

/* Signal handler */
void handle_signal(int signal)
{
    if (signal == SIGUSR1)
        usr1_received = 1;

    else if (signal == SIGUSR2)
        usr2_received = 1;

    else if (signal == SIGCHLD)
    {
        waitpid(-1, NULL, WNOHANG);
        child_finished = 1;
    }

    else if (signal == SIGINT || signal == SIGTERM)
        terminate = 1;
}

int main()
{
    pid_t child_pid;
    sigset_t block_set;

    /* Install signal handlers */
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    signal(SIGCHLD, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("===== Signal Handling Framework =====\n");
    printf("Parent PID: %d\n", getpid());

    /* Create child process */
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    {
        printf("Child process started. PID: %d\n", getpid());
        sleep(5);
        printf("Child process finished.\n");
        exit(0);
    }

    printf("Child PID: %d\n", child_pid);

    /* Block SIGUSR1 */
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &block_set, NULL);

    printf("\nSIGUSR1 is blocked for 10 seconds.\n");
    printf("Open another terminal and run:\n");
    printf("kill -USR1 %d\n", getpid());

    sleep(10);

    printf("Unblocking SIGUSR1...\n");

    sigprocmask(SIG_UNBLOCK, &block_set, NULL);

    printf("\nWaiting for signals...\n");
    printf("Use SIGUSR1, SIGUSR2, SIGTERM or press Ctrl+C.\n");

    while (!terminate)
    {
        sleep(1);

        if (usr1_received)
        {
            printf("SIGUSR1 received successfully.\n");
            usr1_received = 0;
        }

        if (usr2_received)
        {
            printf("SIGUSR2 received successfully.\n");
            usr2_received = 0;
        }

        if (child_finished)
        {
            printf("SIGCHLD received: Child process was reaped.\n");
            child_finished = 0;
        }
    }

    printf("\nTermination signal received.\n");
    printf("Program terminated gracefully.\n");

    return 0;
}
