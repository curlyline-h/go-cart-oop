#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "Order.h"

Order::Order(int orderID, int userID, array<CartItem^>^ items, double total) {
    this->orderID = orderID;
    this->userID = userID;
    this->items = items;
    this->total = total;
    this->orderDate = DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss");
}

int Order::getOrderID() { return orderID; }
int Order::getUserID() { return userID; }
array<CartItem^>^ Order::getItems() { return items; }
double Order::getTotal() { return total; }
String^ Order::getOrderDate() { return orderDate; }
void Order::setOrderDate(String^ date) { this->orderDate = date; }

String^ Order::generateInvoice() {
    String^ invoice = "Invoice for Order #" + orderID + "\nDate: " + orderDate + "\n\nItems:\n";
    for each (CartItem ^ item in items) {
        if (item != nullptr) {
            invoice += item->getProduct()->getName() + " x" + item->getQuantity() + " = $" + item->getSubtotal() + "\n";
        }
    }
    invoice += "\nTotal: $" + total;
    return invoice;
}