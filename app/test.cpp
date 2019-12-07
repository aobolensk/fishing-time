#include "testuser.h"

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int returnCode = 0;
    returnCode |= QTest::qExec(new TestUser, argc, argv);
    return returnCode;
}
