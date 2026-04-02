#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Wishlist.h"

#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <sstream>

Wishlist::Wishlist(int userID) {
    items = gcnew array<Product^>(MAX_WISHLIST_ITEMS);
    itemCount = 0;
    this->userID = userID;
}

String^ Wishlist::getFilename() {
    return "wishlist_user_" + userID.ToString() + ".txt";
}

void Wishlist::addToWishlist(Product^ product) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getProductID() == product->getProductID()) {
            return;
        }
    }
    if (itemCount < MAX_WISHLIST_ITEMS) {
        items[itemCount++] = product;
    }
}

void Wishlist::removeFromWishlist(int productID) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getProductID() == productID) {
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            break;
        }
    }
}

void Wishlist::moveToCart(Product^ product, int quantity, Cart^ cart) {
    cart->addItem(product, quantity);
    removeFromWishlist(product->getProductID());
}

void Wishlist::saveToFile() {
    std::ofstream file(msclr::interop::marshal_as<std::string>(getFilename()));
    for (int i = 0; i < itemCount; i++) {
        msclr::interop::marshal_context context;
        std::string name = context.marshal_as<std::string>(items[i]->getName());
        std::string category = context.marshal_as<std::string>(items[i]->getCategory());
        file << items[i]->getProductID() << "," << name << "," << items[i]->getPrice() << "," << items[i]->getQuantity() << "," << category << "\n";
    }
    file.close();
}

void Wishlist::loadFromFile() {
    std::ifstream file(msclr::interop::marshal_as<std::string>(getFilename()));
    std::string line;
    itemCount = 0;
    while (std::getline(file, line) && itemCount < MAX_WISHLIST_ITEMS) {
        int id, qty;
        double price;
        std::string name, category;
        size_t pos = 0;
        id = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        name = line.substr(0, pos = line.find(","));
        line.erase(0, pos + 1);
        price = std::stod(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        qty = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        category = line;
        items[itemCount++] = gcnew Product(id, gcnew String(name.c_str()), price, qty, gcnew String(category.c_str()));
    }
    file.close();
}

array<Product^>^ Wishlist::getItems() {
    array<Product^>^ result = gcnew array<Product^>(itemCount);
    for (int i = 0; i < itemCount; i++) {
        result[i] = items[i];
    }
    return result;
}