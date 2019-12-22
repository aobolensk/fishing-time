#include "aboutmenu.h"
#include "testuser.h"

int main(int argc, char *argv[]) {
    qInfo() << "OS:" << AboutMenu::getSystemInfo();
    qInfo() << "Compiler:" << AboutMenu::getCompilerInfo();
    int returnCode = 0;
    returnCode |= QTest::qExec(new TestUser, argc, argv);
    return returnCode;
}
