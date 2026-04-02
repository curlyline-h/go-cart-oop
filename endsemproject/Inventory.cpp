#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Inventory.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>

Inventory::Inventory() {
    products = gcnew array<Product^>(MAX_PRODUCTS);
    productCount = 0;
}

void Inventory::addProduct(Product^ p) {
    if (productCount < MAX_PRODUCTS) {
        products[productCount++] = p;
    }
}

void Inventory::updateProduct(int id, Product^ p) {
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == id) {
            products[i] = p;
            break;
        }
    }
}

void Inventory::deleteProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == id) {
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            break;
        }
    }
}

Product^ Inventory::getProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == id) {
            return products[i];
        }
    }
    return nullptr;
}

array<Product^>^ Inventory::searchProducts(String^ keyword) {
    array<Product^>^ results = gcnew array<Product^>(MAX_PRODUCTS);
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getName()->ToLower()->Contains(keyword->ToLower())) {
            results[count++] = products[i];
        }
    }
    array<Product^>^ trimmed = gcnew array<Product^>(count);
    for (int i = 0; i < count; i++) {
        trimmed[i] = results[i];
    }
    return trimmed;
}

array<Product^>^ Inventory::filterByCategory(String^ category) {
    array<Product^>^ results = gcnew array<Product^>(MAX_PRODUCTS);
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getCategory()->ToLower() == category->ToLower()) {
            results[count++] = products[i];
        }
    }
    array<Product^>^ trimmed = gcnew array<Product^>(count);
    for (int i = 0; i < count; i++) {
        trimmed[i] = results[i];
    }
    return trimmed;
}

void Inventory::saveToFile() {
    std::ofstream file("inventory.txt");
    for (int i = 0; i < productCount; i++) {
        msclr::interop::marshal_context context;
        std::string name = context.marshal_as<std::string>(products[i]->getName());
        std::string category = context.marshal_as<std::string>(products[i]->getCategory());
        std::string imagePath = context.marshal_as<std::string>(products[i]->getImagePath());
        file << products[i]->getProductID() << "," << name << "," << products[i]->getPrice() << ","
            << products[i]->getQuantity() << "," << category << "," << imagePath << "\n";
    }
    file.close();
}

void Inventory::loadFromFile() {
    std::ifstream file("inventory.txt");
    std::string line;
    productCount = 0;
    while (std::getline(file, line) && productCount < MAX_PRODUCTS) {
        int id, qty;
        double price;
        std::string name, category, imagePath;
        size_t pos = 0;
        id = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        name = line.substr(0, pos = line.find(","));
        line.erase(0, pos + 1);
        price = std::stod(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        qty = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        category = line.substr(0, pos = line.find(","));
        line.erase(0, pos + 1);
        imagePath = line;
        products[productCount++] = gcnew Product(id, gcnew String(name.c_str()), price, qty,
            gcnew String(category.c_str()), gcnew String(imagePath.c_str()));
    }
    file.close();
}

void Inventory::updateQuantity(int productID, int deltaQty) {
    for each(Product ^ p in products) {
        if (p != nullptr && p->getProductID() == productID) {
            int newQty = p->getQuantity() + deltaQty;
            if (newQty < 0) newQty = 0;
            p->setQuantity(newQty);
            break;
        }
    }
}