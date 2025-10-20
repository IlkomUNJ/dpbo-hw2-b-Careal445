#include <iostream>
#include "userdb.h"

int main() {
    UserDB db("test_users.db");
    User u;
    if (!db.addUser("testuser", "secret", false, u)) {
        std::cout << "addUser failed (maybe exists)" << std::endl;
    } else {
        std::cout << "Added user id=" << u.id << " name=" << u.name << std::endl;
    }
    User auth;
    if (db.authenticate("testuser", "secret", auth)) {
        std::cout << "Authenticate OK id=" << auth.id << " name=" << auth.name << std::endl;
    } else {
        std::cout << "Authenticate failed" << std::endl;
    }
    return 0;
}
