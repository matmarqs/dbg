#include "libdbg/process.h"
#include "str_view.h"
#include <libdbg/libdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <editline/readline.h>
#include <string.h>

void handle_command(process_t *process, char *line) {
    str_view_t line_view = str_view_from_cstr(line);
    str_view_t args[MAX_COMMAND_ARGS];
    split_by_whitespace(line_view, args);
    str_view_t command = args[0];

    if (is_prefix(command, str_view_from_cstr("continue"))) {
        proc_resume(process);
        proc_waitOnSignal(process);
    }
    else {
        fprintf(stderr, "Unknown command\n");
    }
    return;
}

int main(int argc, const char **argv) {
    if (argc == 1) {
        usage();
        return -1;
    }

    process_t proc = attach(argc, argv);

    char *line = NULL;
    while ((line = readline("dbg> ")) != NULL) {
        char *line_cmd = "";
        if (line[0] == '\0') {
            if (history_length > 0) {
                line_cmd = (char *) history_list()[history_length - 1]->line;
            }
        }
        else {
            line_cmd = line;
            add_history(line);
        }

        if (line_cmd[0] != '\0') {
            /* line_str is not empty string */
            handle_command(&proc, line_cmd);
        }
        free(line);
    }

    return 0;
}
