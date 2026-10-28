#include <libdbg/libdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <editline/readline.h>
#include <string.h>

#define UNUSED(x) (void)(x)

void handle_command(pid_t pid, const char *line) {
    UNUSED(pid);
    UNUSED(line);
    return;
}

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
        return -1;
    }

    char *line = NULL;
    while ((line = readline("dbg> ")) != NULL) {
        char *line_str;
        if (strncmp(line, "", 0) == 0) {
            free(line);
            if (history_length > 0) {
                line_str = (char *) history_list()[history_length - 1]->line;
            }
        }
        else {
            line_str = line;
            add_history(line);
            free(line);
        }

        if (line_str[0] != '\0') {
            /* line_str is not empty string */
            handle_command(pid, line_str);
        }
    }

    return 0;
}
