#include "str_view.h"
#include <string.h>
#include <ctype.h>

str_view_t str_view_from_cstr(char *c_str) {
    return (str_view_t) {
        .str = c_str,
        .len = strlen(c_str)
    };
}

bool is_prefix(str_view_t view, str_view_t of) {
    return true;
}

str_view_t trim_by_whitespace(str_view_t view) {
    char *str = view.str;
    int len = view.len;

    if (len == 0) {
        return view;
    }

    int i = 0;
    while (i < len && isspace(str[i])) {
        i++;
    }
    /* i now points to the first non-whitespace character */

    if (i == len) {
        /* the string is only whitespace */
        return (str_view_t) {
            .str = str + len,
            .len = 0
        };
    }

    int j = len-1;
    while (isspace(j)) {
        j--;
    }
    /* j now points to the last non-whitespace character */

    return (str_view_t) {
        .str = str + i,
        .len  = j - i + 1
    };
}

/* return the number of arguments */
int split_by_whitespace(str_view_t view, str_view_t args[MAX_COMMAND_ARGS]) {
    view = trim_by_whitespace(view);
    char *str = view.str;
    int len = view.len;

    if (len == 0) {
        return 0;
    }

    /* we are guaranteed by trim_by_whitespace that
     * the first character is non-whitespace*/
    int start = 0, a = 0;
    while (a < MAX_COMMAND_ARGS) {
        bool done = false;
        int j = start;
        while (!done) {
            if (!isspace(str[j])) {
                j++;
            }
            else if (str[j] == '\0') {
                args[a].str = str + start;
                args[a].len = j - start;
                return a;
            }
            else {
                /* j is whitespace, but not the last null character*/
                args[a].str = str + start;
                args[a].len = j - start;
                a++;
                start = j;
                while (isspace(start)) {
                    start++;
                }
                continue;
            }
        }
    }

    return a;
}
