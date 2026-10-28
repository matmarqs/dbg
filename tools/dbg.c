#include <libdbg/libdbg.h>
#include <stdio.h>

int main(int argc, const char **argv) {
    if (argc == 1) {
        fputs("No arguments given", stderr);
        return -1;
    }

    pid_t pid = attach(argc, argv);
}
