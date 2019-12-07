#include "testuser.h"

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    QTest::qExec(new TestUser, argc, argv);
    return 0;
}
