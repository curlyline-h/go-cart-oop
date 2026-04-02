#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "CartItem.h"

CartItem::CartItem(Product^ product, int quantity) {
    this->product = product;
    this->quantity = quantity;
}

Product^ CartItem::getProduct() { return product; }
int CartItem::getQuantity() { return quantity; }
void CartItem::setQuantity(int quantity) { this->quantity = quantity; }

double CartItem::getSubtotal() {
    return product->getPrice() * quantity;
}