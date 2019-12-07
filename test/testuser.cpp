#include <QCryptographicHash>
#include "testuser.h"
#include "user.h"

void TestUser::getUsername() {
    User user("username", "password");
    QCOMPARE(user.getUsername(), QString("username"));
}
