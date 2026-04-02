// Wishlist.h
#pragma once
#include "Product.h"
#include "Cart.h"
#define MAX_WISHLIST_ITEMS 50

using namespace System;

public ref class Wishlist {
private:
    array<Product^>^ items;
    int itemCount;
    int userID;

    String^ getFilename();

public:
    Wishlist(int userID);
    void addToWishlist(Product^ product);
    void removeFromWishlist(int productID);
    void moveToCart(Product^ product, int quantity, Cart^ cart);
    void saveToFile();
    void loadFromFile();
    array<Product^>^ getItems();
};