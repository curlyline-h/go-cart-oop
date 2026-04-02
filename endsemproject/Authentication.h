#pragma once
#include "User.h"
#define MAX_USERS 50

using namespace System;

public ref class Authentication {
private:
    array<User^>^ users;
    int userCount;
    User^ currentUser;

public:
    Authentication();
    bool signup(String^ username, String^ password, bool isAdmin);
    bool login(String^ username, String^ password);
    void logout();
    User^ getCurrentUser();
    void saveToFile();
    void loadFromFile();
};