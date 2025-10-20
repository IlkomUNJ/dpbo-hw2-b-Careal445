#ifndef USERDB_H
#define USERDB_H

#include "user.h"
#include <vector>
#include <string>

class UserDB {
private:
    std::vector<User> users;
    std::string filename;
    int nextId;

    static std::string escape(const std::string& s) {
        std::string out;
        for (char c : s) {
            if (c == '\\') out += "\\\\";
            else if (c == '|') out += "\\|";
            else out += c;
        }
        return out;
    }

    static std::string unescape(const std::string& s) {
        std::string out;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '\\' && i + 1 < s.size()) {
                ++i;
                out += s[i];
            } else out += s[i];
        }
        return out;
    }

public:
    UserDB(const std::string& filename) : filename(filename), nextId(1) {
        load();
    }

    bool addUser(const std::string& name, const std::string& password, bool isSeller, User &outUser) {
        // ensure unique name
        for (auto &u : users) if (u.name == name) return false;
        User u;
        u.id = nextId++;
        u.name = name;
        u.password = password;
        u.isSeller = isSeller;
        u.bankAccountId = -1;
        users.push_back(u);
        save();
        outUser = u;
        return true;
    }

    bool authenticate(const std::string& name, const std::string& password, User &outUser) {
        for (auto &u : users) {
            if (u.name == name && u.password == password) {
                outUser = u;
                return true;
            }
        }
        return false;
    }

    bool updateUser(const User& user) {
        for (auto &u : users) {
            if (u.id == user.id) {
                u = user;
                save();
                return true;
            }
        }
        return false;
    }

    void load();
    void save();
};

#endif // USERDB_H
