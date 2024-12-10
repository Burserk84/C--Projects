#ifndef IMPERISHABLEPRODUCT_CPP
#define IMPERISHABLEPRODUCT_CPP

#include <iostream>
#include <string>
#include "Product.cpp"
using namespace std;

class ImPerishableProduct : public Product {
public:
    ImPerishableProduct(int id, string name, double price, int quantity);
    ~ImPerishableProduct();
    void display();
};

ImPerishableProduct::ImPerishableProduct(int id, string name, double price, int quantity)
    : Product(id, name, price, quantity) {}

ImPerishableProduct::~ImPerishableProduct() {}

void ImPerishableProduct::display() {
    cout << "ImPerishable Product - ID: " << id << ", Name: " << name << ", Price: " << price << "$, Quantity: " << quantity << endl;
}

#endif // IMPERISHABLEPRODUCT_CPP
