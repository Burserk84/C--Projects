#ifndef PERISHABLEPRODUCT_CPP
#define PERISHABLEPRODUCT_CPP

#include <iostream>
#include <string>
#include <regex>
#include "Product.cpp"
using namespace std;

class PerishableProduct : public Product {
    string expirationDate;

public:
    PerishableProduct(int id, string name, double price, int quantity, string expirationDate);
    ~PerishableProduct();
    string getExpirationDate();
    static bool isValidDate(const string& date);
    void display();
};

PerishableProduct::PerishableProduct(int id, string name, double price, int quantity, string expirationDate)
    : Product(id, name, price, quantity), expirationDate(expirationDate) {}

PerishableProduct::~PerishableProduct() {}

string PerishableProduct::getExpirationDate() {
    return expirationDate;
}

bool PerishableProduct::isValidDate(const string& date) {
    regex pattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, pattern);
}

void PerishableProduct::display() {
    cout << "Perishable Product - ID: " << id << ", Name: " << name << ", Price: " << price << "$, Quantity: " << quantity << ", Expiration Date: " << expirationDate << endl;
}

#endif // PERISHABLEPRODUCT_CPP
