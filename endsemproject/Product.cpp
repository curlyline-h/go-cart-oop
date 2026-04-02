#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Product.h"

Product::Product() : productID(0), name(""), price(0.0), quantity(0), category(""), imagePath("") {}

Product::Product(int id, String^ name, double price, int qty, String^ category) {
    this->productID = id;
    this->name = name;
    this->price = price;
    this->quantity = qty;
    this->category = category;
    this->imagePath = ""; // Default to empty string
}

Product::Product(int id, String^ name, double price, int qty, String^ category, String^ imagePath) {
    this->productID = id;
    this->name = name;
    this->price = price;
    this->quantity = qty;
    this->category = category;
    this->imagePath = imagePath;
}

int Product::getProductID() { return productID; }
String^ Product::getName() { return name; }
double Product::getPrice() { return price; }
int Product::getQuantity() { return quantity; }
String^ Product::getCategory() { return category; }
String^ Product::getImagePath() { return imagePath; }

void Product::setName(String^ name) { this->name = name; }
void Product::setPrice(double price) { this->price = price; }
void Product::setQuantity(int qty) { this->quantity = qty; }
void Product::setCategory(String^ category) { this->category = category; }
void Product::setImagePath(String^ imagePath) { this->imagePath = imagePath; }

String^ Product::display() {
    return "ID: " + productID + ", Name: " + name + ", Price: $" + price + ", Qty: " + quantity + ", Category: " + category + ", Image: " + imagePath;
}