#ifndef ORDER_CPP
#define ORDER_CPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Order {
    string customerName;
    vector<pair<Product*, int>> orderedProducts;

public:
    Order(string customerName) : customerName(customerName) {}
    ~Order() {}

    void addProduct(Product* product, int quantity) {
        orderedProducts.push_back(make_pair(product, quantity));
    }

    void display() {
        cout << "Order for " << customerName << ":" << endl;
        double total = 0.0;
        for (const auto& op : orderedProducts) {
            cout << "Product ID: " << op.first->getId() << ", Name: " << op.first->getName() << ", Price: " << op.first->getPrice() << "$, Quantity: " << op.second << endl;
            total += op.first->getPrice() * op.second;
        }
        cout << "Total Price: " << total << "$" << endl;
    }

    string getCustomerName() {
        return customerName;
    }

    const vector<pair<Product*, int>>& getOrderedProducts() {
        return orderedProducts;
    }
};

#endif // ORDER_CPP
