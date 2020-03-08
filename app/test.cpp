#include "aboutmenu.h"
#include "testuser.h"
#include "testconfig.h"
#include "testinventory.h"

int main(int argc, char *argv[]) {
    qInfo() << "OS:" << AboutMenu::getSystemInfo();
    qInfo() << "Compiler:" << AboutMenu::getCompilerInfo();
    int returnCode = 0;
    returnCode |= QTest::qExec(new TestUser, argc, argv);
    returnCode |= QTest::qExec(new TestConfig, argc, argv);
    returnCode |= QTest::qExec(new TestInventory, argc, argv);
    return returnCode;
}
