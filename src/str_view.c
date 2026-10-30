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

int str_view_cmp(str_view_t a, str_view_t b) {
    int len_a = a.len;
    int len_b = b.len;
    int min_len = len_a < len_b ? len_a : len_b;
    int result = strncmp(a.str, b.str, min_len);
    if (result == 0) {
        if (len_a < len_b)
            return -1;
        else if (len_a == len_b)
            return 0;
        else
            return 1;
    }
    return result;
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
    while (isspace(str[j])) {
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
     * the first character is non-whitespace */
    int start = 0, a = 0;
    int j = start;
    while (true) {
        if (!isspace(str[j])) {
            j++;
        }
        else if (j >= len || str[j] == '\0') {
            args[a].str = str + start;
            args[a].len = j - start;
            a++;
            return a;
        }
        else {
            /* j is whitespace, but not the last null character*/
            args[a].str = str + start;
            args[a].len = j - start;
            a++;
            if (a >= MAX_COMMAND_ARGS)
                return a;
            start = j;
            while (isspace(str[start])) {
                start++;
            }
            j = start;
        }
    }

    return a;
}
