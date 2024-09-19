#include <stdio.h>
#include <stdlib.h>  // This is needed for srandom() and random()
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void child_process() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    // Seed the random number generator based on the child PID and time
    srandom(time(NULL) ^ (pid << 16));

    // Random number of iterations (up to 30)
    int num_iterations = random() % 30 + 1;

    for (int i = 0; i < num_iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", pid);

        // Sleep for a random time (1 to 10 seconds)
        int sleep_time = random() % 10 + 1;
        sleep(sleep_time);

        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, ppid);
    }

    // Child terminates here
    printf("Child Pid: %d has finished its work and is exiting.\n", pid);
    exit(0);
}

int main() {
    pid_t pid1, pid2;
    int status;

    // Fork the first child
    pid1 = fork();
    if (pid1 == 0) {
        // Inside first child process
        child_process();
    } else if (pid1 > 0) {
        // Fork the second child
        pid2 = fork();
        if (pid2 == 0) {
            // Inside second child process
            child_process();
        } else if (pid2 > 0) {
            // Parent process: wait for both children to finish

            // Wait for the first child
            pid_t finished_child = wait(&status);
            printf("Child Pid: %d has completed.\n", finished_child);

            // Wait for the second child
            finished_child = wait(&status);
            printf("Child Pid: %d has completed.\n", finished_child);

            printf("Parent process has finished.\n");
        } else {
            // Forking second child failed
            perror("Fork failed for the second child");
            exit(1);
        }
    } else {
        // Forking first child failed
        perror("Fork failed for the first child");
        exit(1);
    }

    return 0;
}
