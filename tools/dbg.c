#include "str_view.h"
#include <libdbg/libdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <editline/readline.h>
#include <string.h>

void handle_command(pid_t pid, const char *line) {
    /* max 8 arguments for now */
    str_view_t args[MAX_COMMAND_ARGS] = { 0 };
    str_view_t command = str_view_from_cstr(line);
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
        char *line_c_str = "";
        if (strncmp(line, "", 0) == 0) {
            free(line);
            if (history_length > 0) {
                line_c_str = (char *) history_list()[history_length - 1]->line;
            }
        }
        else {
            line_c_str = line;
            add_history(line);
            free(line);
        }

        if (line_c_str[0] != '\0') {
            /* line_str is not empty string */
            handle_command(pid, line_c_str);
        }
    }

    return 0;
}
