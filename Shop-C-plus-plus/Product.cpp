#ifndef PRODUCT_CPP
#define PRODUCT_CPP

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product(int id, string name, double price, int quantity);
    virtual ~Product();
    int getId();
    string getName();
    double getPrice();
    int getQuantity();
    void reduceQuantity(int amount);
    virtual void display() = 0;
};

Product::Product(int id, string name, double price, int quantity) 
    : id(id), name(name), price(price), quantity(quantity) {}

Product::~Product() {}

int Product::getId() {
    return id;
}

string Product::getName() {
    return name;
}

double Product::getPrice() {
    return price;
}

int Product::getQuantity() {
    return quantity;
}

void Product::reduceQuantity(int amount) {
    if (quantity >= amount) {
        quantity -= amount;
    }
}

#endif // PRODUCT_CPP
