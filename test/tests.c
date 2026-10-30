#include "test_t.h"
#include "str_view.h"
#include <stdio.h>

/* BEGIN TESTS */

bool test_trim_by_ws() {
    str_view_t s = str_view_from_cstr("  \n  Hello just a test here  \t   ");
    str_view_t t = str_view_from_cstr("Hello just a test here");
    s = trim_by_whitespace(s);
    t = trim_by_whitespace(t);
    /* they should be equal */
    if (str_view_cmp(s, t) != 0) {
        puts(FAIL "failed on 1 test_trim_by_ws");
        return false;
    }

    s = str_view_from_cstr("  \n  Another test\n\n\n\t   \r");
    t = str_view_from_cstr("\nAnother test    ");
    s = trim_by_whitespace(s);
    t = trim_by_whitespace(t);
    /* they should be equal */
    if (str_view_cmp(s, t) != 0) {
        puts(FAIL "failed on 2 test_trim_by_ws");
        return false;
    }

    s = str_view_from_cstr("  \n  Third test\n\n\n\t   \r");
    t = str_view_from_cstr("\nThird test   x ");
    s = trim_by_whitespace(s);
    t = trim_by_whitespace(t);
    /* they should be different */
    if (str_view_cmp(s, t) == 0) {
        puts(FAIL "failed on 3 test_trim_by_ws");
        return false;
    }

    return true;
}

bool test_split_by_ws() {
    str_view_t s = str_view_from_cstr("  \n  Hello\n \t just \r a \n\ftest   here  \t   ");
    str_view_t expected[MAX_COMMAND_ARGS] = {
        str_view_from_cstr("Hello"),
        str_view_from_cstr("just"),
        str_view_from_cstr("a"),
        str_view_from_cstr("test"),
        str_view_from_cstr("here"),
    };
    str_view_t result[MAX_COMMAND_ARGS];
    int num_args = split_by_whitespace(s, result);
    if (num_args != 5)
        return false;
    for (int i = 0; i < num_args; i++) {
        if (str_view_cmp(result[i], expected[i]) != 0)
            return false;
    }

    s = str_view_from_cstr("  \n  break \nset\t *0x8888  \t   ");
    str_view_t expected_2[MAX_COMMAND_ARGS] = {
        str_view_from_cstr("break"),
        str_view_from_cstr("set"),
        str_view_from_cstr("*0x8888"),
    };
    num_args = split_by_whitespace(s, result);
    if (num_args != 3)
        return false;
    for (int i = 0; i < num_args; i++) {
        if (str_view_cmp(result[i], expected_2[i]) != 0)
            return false;
    }

    s = str_view_from_cstr("cont");
    str_view_t expected_3[MAX_COMMAND_ARGS] = {
        str_view_from_cstr("cont"),
    };
    num_args = split_by_whitespace(s, result);
    if (num_args != 1)
        return false;
    for (int i = 0; i < num_args; i++) {
        if (str_view_cmp(result[i], expected_3[i]) != 0)
            return false;
    }

    return true;
}

bool test_is_prefix() {
    if (is_prefix(str_view_from_cstr("c"), str_view_from_cstr("continue")) != true)
        return false;
    if (is_prefix(str_view_from_cstr("cont"), str_view_from_cstr("continue")) != true)
        return false;
    if (is_prefix(str_view_from_cstr("continue"), str_view_from_cstr("continue")) != true)
        return false;
    if (is_prefix(str_view_from_cstr("continuee"), str_view_from_cstr("continue")) != false)
        return false;
    return true;
}

test_t tests[] = {
    REGISTER_TEST(test_trim_by_ws),
    REGISTER_TEST(test_split_by_ws),
    REGISTER_TEST(test_is_prefix),
};

/* END TESTS */

int main() {
    int failed = 0;
    int total = LEN(tests);

    for (int i = 0; i < total; i++) {
        bool result = tests[i].func();
        if (result) {
            printf(PASS "%s: passed\n", tests[i].name);
        }
        else {
            failed++;
            printf(FAIL "%s: failed\n", tests[i].name);
        }
    }

    if (failed == 0) {
        printf(PASS "All tests passed\n");
    }
    else {
        printf(FAIL "test cases: %d | %d failed\n", failed, total);
    }

    return 0;
}
