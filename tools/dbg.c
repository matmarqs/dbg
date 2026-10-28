#include <libdbg/libdbg.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, const char **argv) {
    if (argc == 1) {
        fputs("No arguments given", stderr);
        return -1;
    }

    pid_t pid = attach(argc, argv);

    int wait_status;
    int options = 0;
    if (waitpid(pid, &wait_status, options) < 0) {
        perror("waitpid failed");
    }
}
