#pragma once
#include "CartItem.h"
using namespace System;
using namespace System::Collections::Generic;

public ref class Cart {
private:
    List<CartItem^>^ items;
    String^ appliedDiscountCode;

public:
    Cart();
    void addItem(Product^ product, int quantity);
    void removeItem(int productID);
    void updateQuantity(int productId, int qtyToRemove);
    bool applyDiscount(String^ code);
    double calculateTotal();
    void clearCart();
    array<CartItem^>^ getItems();
};
