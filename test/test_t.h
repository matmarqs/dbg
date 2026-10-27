#ifndef DBG_TESTS_H
#define DBG_TESTS_H

#include <stdbool.h>

#define FAIL "\e[0;31m"
#define PASS "\e[0;32m"
#define NORMAL "\e[0;37m"

#define LEN(x) (sizeof(x) / sizeof(x[0]))
#define REGISTER_TEST(f) { f, #f }

typedef bool (*test_func)(void);

typedef struct {
    test_func func;
    const char *name;
} test_t;

#endif
