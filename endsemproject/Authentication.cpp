#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Authentication.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>

Authentication::Authentication() {
    users = gcnew array<User^>(MAX_USERS);
    userCount = 0;
    currentUser = nullptr;
}

bool Authentication::signup(String^ username, String^ password, bool isAdmin) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUsername() == username) {
            return false;
        }
    }
    if (userCount < MAX_USERS) {
        users[userCount++] = gcnew User(userCount, username, password, isAdmin);
        saveToFile();
        return true;
    }
    return false;
}

bool Authentication::login(String^ username, String^ password) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == users[i]->hashPassword(password)) {
            currentUser = users[i];
            return true;
        }
    }
    return false;
}

void Authentication::logout() {
    currentUser = nullptr;
}

User^ Authentication::getCurrentUser() {
    return currentUser;
}

void Authentication::saveToFile() {
    std::ofstream file("users.txt");
    for (int i = 0; i < userCount; i++) {
        msclr::interop::marshal_context context;
        std::string username = context.marshal_as<std::string>(users[i]->getUsername());
        std::string password = context.marshal_as<std::string>(users[i]->getPassword());
        file << users[i]->getUserID() << "," << username << "," << password << "," << users[i]->getIsAdmin() << "\n";
    }
    file.close();
}

void Authentication::loadFromFile() {
    std::ifstream file("users.txt");
    std::string line;
    userCount = 0;
    while (std::getline(file, line) && userCount < MAX_USERS) {
        int id, isAdmin;
        std::string username, password;
        size_t pos = 0;
        id = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        username = line.substr(0, pos = line.find(","));
        line.erase(0, pos + 1);
        password = line.substr(0, pos = line.find(","));
        line.erase(0, pos + 1);
        isAdmin = std::stoi(line);
        users[userCount++] = gcnew User(id, gcnew String(username.c_str()), gcnew String(password.c_str()), isAdmin);
    }
    file.close();
}