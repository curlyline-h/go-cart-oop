#include "Cart.h"
using namespace System::Collections::Generic;

Cart::Cart() {
    items = gcnew List<CartItem^>();
    appliedDiscountCode = "";
}

void Cart::addItem(Product^ product, int quantity) {
    for each (CartItem ^ item in items) {
        if (item->getProduct()->getProductID() == product->getProductID()) {
            item->setQuantity(item->getQuantity() + quantity);
            return;
        }
    }
    items->Add(gcnew CartItem(product, quantity));
}

void Cart::removeItem(int productID) {
    for (int i = 0; i < items->Count; i++) {
        if (items[i]->getProduct()->getProductID() == productID) {
            items->RemoveAt(i);
            break;
        }
    }
}

void Cart::updateQuantity(int productId, int qtyToRemove) {
    for (int i = 0; i < items->Count; i++) {
        CartItem^ item = items[i];
        if (item->getProduct()->getProductID() == productId) {
            int remaining = item->getQuantity() - qtyToRemove;
            if (remaining <= 0) {
                items->RemoveAt(i);
            }
            else {
                item->setQuantity(remaining);
            }
            break;
        }
    }
}

bool Cart::applyDiscount(String^ code) {
    if (code == "SAVE10") {
        appliedDiscountCode = code;
        return true;
    }
    return false;
}

double Cart::calculateTotal() {
    double total = 0;
    for each (CartItem ^ item in items) {
        total += item->getSubtotal();
    }
    if (appliedDiscountCode == "SAVE10") {
        total *= 0.9;
    }
    return total;
}

void Cart::clearCart() {
    items->Clear();
    appliedDiscountCode = "";
}

array<CartItem^>^ Cart::getItems() {
    return items->ToArray();
}
