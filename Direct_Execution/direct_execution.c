#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    /*
    //measure the time for system calls
    struct timeval start, end;
    //measuring 1000 system calls
    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000; i++){
        printf("%d\n", i);
    }
    gettimeofday(&end, NULL);

    printf("%f", ((end.tv_sec - start.tv_sec) + 
    (end.tv_usec - start.tv_usec) / 1e6) / 1000); */

    /*
    cpu_set_t set;
    pid_t pid = getpid();  // Get current process ID

    // Initialize the CPU set and assign CPU 0 and 1 to the process
    CPU_ZERO(&set);         // Clear the CPU set
    CPU_SET(4, &set);       // Add CPU 0

    // Set CPU affinity for the current process
    if (sched_setaffinity(pid, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        return 1;
    }

    // Verify the CPU affinity
    CPU_ZERO(&set);  // Clear the set before checking
    if (sched_getaffinity(pid, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_getaffinity");
        return 1;
    }

    // Print the CPU affinity
    printf("Current CPU Affinity: ");
    for (int i = 0; i < CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &set)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    while(1){
        //do nothing;
    } */

    //benchmark context switches
    int fd[2];  // File descriptors: fd[0] for reading, fd[1] for writing
    pid_t pid;
    if (pipe(fd) == -1) {  // Create pipe
        perror("pipe failed");
        exit(1);
    }
    //set cpu affinity which will be inhertied by child
    cpu_set_t set;
    pid_t pid = getpid();  // Get current process ID

    // Initialize the CPU set and assign CPU 0 and 1 to the process
    CPU_ZERO(&set);         // Clear the CPU set
    CPU_SET(0, &set);       // Add CPU 0

    // Set CPU affinity for the current process
    if (sched_setaffinity(pid, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        return 1;
    }

    pid = fork();  // Create child process

    if (pid < 0) {  // Fork failed
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        close(fd[1]);  // Close unused write end

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));  // Read from pipe
        printf("Child received: %s\n", buffer);

        close(fd[0]);  // Close read end
    } else {  // Parent process
        close(fd[0]);  // Close unused read end

        char message[] = "Hello from parent!";
        write(fd[1], message, strlen(message) + 1);  // Write to pipe
        wait();
        close(fd[1]);  // Close write end
    }

    return 0;
}