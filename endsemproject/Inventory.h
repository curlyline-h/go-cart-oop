#pragma once
#include "Product.h"
#define MAX_PRODUCTS 100

using namespace System;
using namespace System::Collections::Generic;

public ref class Inventory {
private:
    array<Product^>^ products;
    int productCount;

public:
    Inventory();
    void updateQuantity(int productID, int deltaQty);
    void addProduct(Product^ p);
    void updateProduct(int id, Product^ p);
    void deleteProduct(int id);
    Product^ getProduct(int id);
    array<Product^>^ searchProducts(String^ keyword);
    array<Product^>^ filterByCategory(String^ category);
    void saveToFile();
    void loadFromFile();
};