#include <windows.h>
#include <servprov.h>
#include <urlmon.h>

#include "OrderHistory.h"
#include "Cart.h"

#include <msclr/marshal_cppstd.h>
#include <fstream>
using namespace System::Collections::Generic;

OrderHistory::OrderHistory() {
    orders = gcnew array<Order^>(MAX_ORDERS);
    orderCount = 0;
}

void OrderHistory::addOrder(Order^ order) {
    if (orderCount < MAX_ORDERS) {
        orders[orderCount++] = order;
    }
}

array<Order^>^ OrderHistory::getOrders(int userID) {
    array<Order^>^ userOrders = gcnew array<Order^>(MAX_ORDERS);
    int count = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i]->getUserID() == userID) {
            userOrders[count++] = orders[i];
        }
    }
    array<Order^>^ trimmed = gcnew array<Order^>(count);
    for (int i = 0; i < count; i++) {
        trimmed[i] = userOrders[i];
    }
    return trimmed;
}
int OrderHistory::getNextOrderID() {
    return orderCount + 1;
}
array<CartItem^>^ OrderHistory::reorder(int orderID) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i]->getOrderID() == orderID) {
            return orders[i]->getItems();
        }
    }
    return gcnew array<CartItem^>(0);
}

void OrderHistory::saveToFile() {
    std::ofstream file("orders.txt");
    for (int i = 0; i < orderCount; i++) {
        msclr::interop::marshal_context context;
        std::string date = context.marshal_as<std::string>(orders[i]->getOrderDate());
        file << orders[i]->getOrderID() << "," << orders[i]->getUserID() << "," << orders[i]->getTotal() << "," << date << "\n";
        for each (CartItem ^ item in orders[i]->getItems()) {
            if (item != nullptr) {
                std::string name = context.marshal_as<std::string>(item->getProduct()->getName());
                std::string category = context.marshal_as<std::string>(item->getProduct()->getCategory());
                file << item->getProduct()->getProductID() << "," << name << "," << item->getProduct()->getPrice() << "," << item->getQuantity() << "," << category << "\n";
            }
        }
        file << "END\n";
    }
    file.close();
}

void OrderHistory::loadFromFile() {
    std::ifstream file("orders.txt");
    std::string line;
    orderCount = 0;

    while (std::getline(file, line) && orderCount < MAX_ORDERS) {
        int orderID, userID;
        double total;
        std::string date;
        size_t pos = 0;

        orderID = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        userID = std::stoi(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        total = std::stod(line.substr(0, pos = line.find(",")));
        line.erase(0, pos + 1);
        date = line;

        // Use List instead of fixed-size array
        List<CartItem^>^ itemsList = gcnew List<CartItem^>();

        while (std::getline(file, line) && line != "END") {
            int id, qty;
            double price;
            std::string name, category;

            pos = 0;
            id = std::stoi(line.substr(0, pos = line.find(",")));
            line.erase(0, pos + 1);
            name = line.substr(0, pos = line.find(","));
            line.erase(0, pos + 1);
            price = std::stod(line.substr(0, pos = line.find(",")));
            line.erase(0, pos + 1);
            qty = std::stoi(line.substr(0, pos = line.find(",")));
            line.erase(0, pos + 1);
            category = line;

            Product^ p = gcnew Product(id, gcnew String(name.c_str()), price, qty, gcnew String(category.c_str()));
            itemsList->Add(gcnew CartItem(p, qty));
        }

        // Convert to array before storing
        array<CartItem^>^ trimmedItems = itemsList->ToArray();
        orders[orderCount] = gcnew Order(orderID, userID, trimmedItems, total);
        orders[orderCount]->setOrderDate(gcnew String(date.c_str()));
        orderCount++;
    }

    file.close();
}
