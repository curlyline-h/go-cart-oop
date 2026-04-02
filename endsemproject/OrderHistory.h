#pragma once
#include "Order.h"
#define MAX_ORDERS 100

using namespace System;

public ref class OrderHistory {
private:
    array<Order^>^ orders;
    int orderCount;

public:
    OrderHistory();
    int getNextOrderID();
    void addOrder(Order^ order);
    array<Order^>^ getOrders(int userID);
    array<CartItem^>^ reorder(int orderID);
    void saveToFile();
    void loadFromFile();
};