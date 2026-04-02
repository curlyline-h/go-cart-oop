#pragma once
#include "CartItem.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Order {
private:
    int orderID;
    int userID;
    array<CartItem^>^ items;
    double total;
    String^ orderDate;

public:
    Order(int orderID, int userID, array<CartItem^>^ items, double total);
    int getOrderID();
    int getUserID();
    array<CartItem^>^ getItems();
    double getTotal();
    String^ getOrderDate();
    void setOrderDate(String^ date);
    String^ generateInvoice();
};