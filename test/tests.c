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

test_t tests[] = {
    REGISTER_TEST(test_trim_by_ws),
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
