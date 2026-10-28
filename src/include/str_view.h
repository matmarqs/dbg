#ifndef DBG_STRVIEW_H
#define DBG_STRVIEW_H

#include <stdbool.h>

#define MAX_COMMAND_ARGS 8

typedef struct {
    char *str;
    int len;
} str_view_t;

str_view_t str_view_from_cstr(char *c_str);

#endif
