#include <stdio.h>
#include <stdlib.h>
#include <libdbg/libdbg.h>
#include <sys/ptrace.h>
#include <string.h>
#include <unistd.h>

void usage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\tdbg executable\tLaunch the debugee\n");
    fprintf(stderr, "\tdbg -p PID\t\tAttach to process PID\n");
}

pid_t attach(int argc, const char **argv) {
    pid_t pid = 0;

    if (argc == 3 && strncmp(argv[1], "-p", 2) == 0) {
        /* argv[2] means PID of the process to attach */
        pid = atoi(argv[2]);
        if (pid <= 0) {
            perror("Invalid pid");
            return -1;
        }
        if (ptrace(PTRACE_ATTACH, pid, /*addr=*/NULL, /*data=*/NULL) < 0) {
            perror("Could not attach");
            return -1;
        }
    }
    else if (argc == 2) {
        /* run and launch, argv[1] means file_path */
        const char *program_path = argv[1];
        if ((pid = fork()) < 0) {
            perror("fork failed");
            return -1;
        }

        if (pid == 0) {
            /* child process */
            if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
                perror("Tracing failed");
                return -1;
            }
            if (execlp(program_path, program_path, NULL) < 0) {
                perror("Exec failed");
                return -1;
            }
        }
    }
    else {
        usage();
        return -1;
    }

    return pid;
}
