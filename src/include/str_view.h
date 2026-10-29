#ifndef DBG_STRVIEW_H
#define DBG_STRVIEW_H

#include <stdbool.h>

#define MAX_COMMAND_ARGS 8

typedef struct {
    char *str;
    int len;
} str_view_t;

str_view_t str_view_from_cstr(char *c_str);
str_view_t trim_by_whitespace(str_view_t view);
int split_by_whitespace(str_view_t view, str_view_t args[MAX_COMMAND_ARGS]);
int str_view_cmp(str_view_t a, str_view_t b);

#endif
