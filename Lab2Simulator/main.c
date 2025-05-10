#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// constant for the number of children
#define NUM_CHILDREN 10

// My commands to run!
char *commands[NUM_CHILDREN][4] = {
    {"echo", "Hello Austin Snyder", NULL},
    {"ls", NULL},
    {"date", NULL},
    {"time", NULL},
    {"history", NULL},
    {"ps", NULL},
    {"touch", "touchedfile.txt", NULL},
    {"mkdir", "-p", "dirDir", NULL},
    {"cat", "Makefile", NULL},
    {"rmdir", "nonExistantDir", NULL}
};

int main() {
    int results[NUM_CHILDREN][2];   // [][0] = pid, [][1] = status
    pid_t pids[NUM_CHILDREN];

    // Fork all children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            // If fork fails exit with message
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // In child: print what it will run
            printf("[Child %d] PID: %d — Executing: %s\n", i, getpid(), commands[i][0]);
            execvp(commands[i][0], commands[i]);

            // if the execvp failed, we print error message.
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // In parent: store PID for later use
            pids[i] = pid;
        }
    }

    // Wait for all children, store results
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t wpid = waitpid(-1, &status, 0); // wait for any child
        results[i][0] = wpid;
        results[i][1] = status;
    }

    // once all the children are done, we print the results 
    printf("\n|||==== Child Exit Summary =====|||\n");
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = results[i][0];
        int status = results[i][1];

        // If it exiteed normally, print the exit status
        if (WIFEXITED(status)) {
            printf("Child PID %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            // If it was terminated by a signal, print the signal number
            printf("Child PID %d terminated by signal %d\n", pid, WTERMSIG(status));
        } else {
            // If it exited abnormally, print the PID
            printf("Child PID %d exited abnormally\n", pid);
        }
    }

    return 0;
}