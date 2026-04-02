#pragma once
#include "Product.h"

using namespace System;

public ref class CartItem : public Product {
private:
    Product^ product;
    int quantity;

public:
    CartItem(Product^ product, int quantity);
    Product^ getProduct();
    int getQuantity();
    void setQuantity(int quantity);
    double getSubtotal();
};