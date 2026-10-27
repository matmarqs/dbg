#include "test_t.h"
#include <stdio.h>

/* BEGIN TESTS */

bool test_environment() {
    return true;
}

bool test_true() {
    return true;
}

test_t tests[] = {
    REGISTER_TEST(test_environment),
    REGISTER_TEST(test_true)
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
