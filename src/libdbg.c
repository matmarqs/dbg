#include <stdio.h>
#include <stdlib.h>
#include <libdbg/libdbg.h>
#include <libdbg/process.h>
#include <sys/ptrace.h>
#include <string.h>
#include <unistd.h>

void usage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\tdbg executable\t\tLaunch the debuggee\n");
    fprintf(stderr, "\tdbg -p PID\t\tAttach to process PID\n");
}

process_t attach(int argc, const char **argv) {
    process_t proc;

    if (argc == 3 && strncmp(argv[1], "-p", 2) == 0) {
        /* argv[2] means PID of the process to attach */
        proc = proc_attach(/*pid=*/atoi(argv[2]));
    }
    else if (argc == 2) {
        /* run and launch, argv[1] means file_path */
        proc = proc_launch(argv[1]);
    }
    else {
        usage();
        exit(EXIT_FAILURE);
    }

    return proc;
}
