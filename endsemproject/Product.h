#pragma once
#include <string>

using namespace System;

public ref class Product {
private:
    int productID;
    String^ name;
    double price;
    int quantity;
    String^ category;
    String^ imagePath; // New field for image path

public:
    Product();
    Product(int id, String^ name, double price, int qty, String^ category);
    Product(int id, String^ name, double price, int qty, String^ category, String^ imagePath); // New constructor

    int getProductID();
    String^ getName();
    double getPrice();
    int getQuantity();
    String^ getCategory();
    String^ getImagePath(); // Getter for image path

    void setName(String^ name);
    void setPrice(double price);
    void setQuantity(int qty);
    void setCategory(String^ category);
    void setImagePath(String^ imagePath); // Setter for image path

    virtual String^ display();
};