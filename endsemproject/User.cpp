#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "User.h"

User::User() : userID(0), username(""), password(""), isAdmin(false) {}

User::User(int id, String^ username, String^ password, bool isAdmin) {
    this->userID = id;
    this->username = username;
    this->password = hashPassword(password);
    this->isAdmin = isAdmin;
}

int User::getUserID() { return userID; }
String^ User::getUsername() { return username; }
String^ User::getPassword() { return password; }
bool User::getIsAdmin() { return isAdmin; }

void User::setUsername(String^ username) { this->username = username; }
void User::setPassword(String^ password) { this->password = hashPassword(password); }
void User::setIsAdmin(bool isAdmin) { this->isAdmin = isAdmin; }

String^ User::hashPassword(String^ password) {
    // Simple hash for demo (in real apps, use secure hashing like bcrypt)
    String^ hashed = "";
    for each (Char c in password) {
        hashed += (Char)(c + 1); // Basic shift for demo
    }
    return hashed;
}