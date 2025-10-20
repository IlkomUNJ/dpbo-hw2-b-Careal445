#include "userdb.h"
#include <fstream>
#include <sstream>

void UserDB::load() {
    users.clear();
    nextId = 1;
    std::ifstream in(filename);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts;
        std::string cur;
        bool esc = false;
        for (char c : line) {
            if (esc) { cur += c; esc = false; }
            else if (c == '\\') esc = true;
            else if (c == '|') { parts.push_back(cur); cur.clear(); }
            else cur += c;
        }
        parts.push_back(cur);
        if (parts.size() < 5) continue;
        User u;
        u.id = std::stoi(parts[0]);
        u.name = unescape(parts[1]);
        u.password = unescape(parts[2]);
        u.isSeller = (parts[3] == "1");
        u.bankAccountId = std::stoi(parts[4]);
        users.push_back(u);
        if (u.id >= nextId) nextId = u.id + 1;
    }
}

void UserDB::save() {
    std::ofstream out(filename, std::ios::trunc);
    for (auto &u : users) {
        out << u.id << '|'
            << escape(u.name) << '|'
            << escape(u.password) << '|'
            << (u.isSeller ? '1' : '0') << '|' << u.bankAccountId << '\n';
    }
}
