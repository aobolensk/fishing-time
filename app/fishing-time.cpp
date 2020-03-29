#include <QApplication>
#include "argparser.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    QApplication::setOrganizationName("aobolensk");
    QApplication::setOrganizationDomain("github.com/aobolensk/fishing-time");
    QApplication::setApplicationName("Fishing Time");
    QApplication::setApplicationVersion(TOSTRING(COMMIT_HASH));
    QApplication app(argc, argv);
    ArgParser argParser;
    return argParser.process();
}
