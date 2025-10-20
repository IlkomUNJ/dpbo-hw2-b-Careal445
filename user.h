#ifndef USER_H
#define USER_H

#include <string>

struct User {
    int id;
    std::string name;
    std::string password; // stored as plain text for simplicity (not for production)
    bool isSeller;
    int bankAccountId; // -1 if none

    User() : id(-1), name(""), password(""), isSeller(false), bankAccountId(-1) {}
};

#endif // USER_H
