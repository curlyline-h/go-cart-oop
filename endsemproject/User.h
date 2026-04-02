#pragma once
#include <string>

using namespace System;

public ref class User {
private:
    int userID;
    String^ username;
    String^ password;
    bool isAdmin;

public:
    User();
    User(int id, String^ username, String^ password, bool isAdmin);

    int getUserID();
    String^ getUsername();
    String^ getPassword();
    bool getIsAdmin();

    void setUsername(String^ username);
    void setPassword(String^ password);
    void setIsAdmin(bool isAdmin);

    String^ hashPassword(String^ password);
};