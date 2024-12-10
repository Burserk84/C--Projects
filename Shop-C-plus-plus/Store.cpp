#ifndef STORE_CPP
#define STORE_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include "Product.cpp"
#include "PerishableProduct.cpp"
#include "ImPerishableProduct.cpp"
#include "Order.cpp"
using namespace std;

class Store {
    vector<Product*> products;
    vector<Order*> orders;

public:
    Store();
    ~Store();
    void addProduct(Product* product);
    void createOrder();
    void displayProducts();
    void displayOrders();
    bool isProductIdUnique(int id);
    bool isProductListEmpty();
    bool isOrderListEmpty();
    void loadProducts();
    void saveProducts();
    void loadOrders();
    void saveOrders();
};
/// constructor to load data
Store::Store() {
    loadProducts();
    loadOrders();
}
/// distructor to save data
Store::~Store() {
    saveProducts();
    saveOrders();
    for (int i = 0; i < products.size(); i++) {
        delete products[i];
    }
    for (int i = 0; i < orders.size(); i++) {
        delete orders[i];
    }
}
/// method to load product
void Store::loadProducts() {
    ifstream perishableFile("perishable_products.txt");
    ifstream imperishableFile("imperishable_products.txt");

    if (perishableFile.is_open()) {
        string line;
        while (getline(perishableFile, line)) {
            stringstream ss(line);
            int id, quantity;
            double price;
            string name, expirationDate;

            ss >> id >> name >> price >> quantity >> expirationDate;
            products.push_back(new PerishableProduct(id, name, price, quantity, expirationDate));
        }
        perishableFile.close();
    }

    if (imperishableFile.is_open()) {
        string line;
        while (getline(imperishableFile, line)) {
            stringstream ss(line);
            int id, quantity;
            double price;
            string name;

            ss >> id >> name >> price >> quantity;
            products.push_back(new ImPerishableProduct(id, name, price, quantity));
        }
        imperishableFile.close();
    }
}
/// method to save products
void Store::saveProducts() {
    ofstream perishableFile("perishable_products.txt");
    ofstream imperishableFile("imperishable_products.txt");

    if (perishableFile.is_open() && imperishableFile.is_open()) {
        for (int i = 0; i < products.size(); i++) {
            PerishableProduct* pp = dynamic_cast<PerishableProduct*>(products[i]);
            if (pp != nullptr) {
                perishableFile << pp->getId() << " " << pp->getName() << " " << pp->getPrice() << " " << pp->getQuantity() << " " << pp->getExpirationDate() << endl;
            } else {
                ImPerishableProduct* ip = dynamic_cast<ImPerishableProduct*>(products[i]);
                if (ip != nullptr) {
                    imperishableFile << ip->getId() << " " << ip->getName() << " " << ip->getPrice() << " " << ip->getQuantity() << endl;
                }
            }
        }
        perishableFile.close();
        imperishableFile.close();
    }
}
/// method to load products
void Store::loadOrders() {
    ifstream orderFile("orders.txt");

    if (orderFile.is_open()) {
        string line;
        while (getline(orderFile, line)) {
            stringstream ss(line);
            string customerName;
            ss >> customerName;

            Order* order = new Order(customerName);
            orders.push_back(order);

            int productId, quantity;
            while (ss >> productId >> quantity) {
                for (int i = 0; i < products.size(); i++) {
                    if (products[i]->getId() == productId) {
                        order->addProduct(products[i], quantity);
                        break;
                    }
                }
            }
        }
        orderFile.close();
    }
}
/// method to save orders
void Store::saveOrders() {
    ofstream orderFile("orders.txt");

    if (orderFile.is_open()) {
        for (int i = 0; i < orders.size(); i++) {
            orderFile << orders[i]->getCustomerName();
            const vector<pair<Product*, int>>& orderedProducts = orders[i]->getOrderedProducts();
            for (const auto& op : orderedProducts) {
                orderFile << " " << op.first->getId() << " " << op.second;
            }
            orderFile << endl;
        }
        orderFile.close();
    }
}
/// method to check if product id exist or not
bool Store::isProductIdUnique(int id) {
    for (int i = 0; i < products.size(); i++) {
        if (products[i]->getId() == id) {
            return false;
        }
    }
    return true;
}
/// mehtod ro check list of products are empty or not
bool Store::isProductListEmpty() {
    return products.empty();
}
/// mehtod ro check list of orders are empty or not
bool Store::isOrderListEmpty() {
    return orders.empty();
}
/// mehtod ro push product details to products vector
void Store::addProduct(Product* product) {
    products.push_back(product);
}
/// mehtod ro create order
void Store::createOrder() {
    if (isProductListEmpty()) {
        cout << "No products available to create an order." << endl;
        return;
    }

    string customerName;
    cout << "Enter customer name: ";
    cin >> customerName;

    Order* order = new Order(customerName);
    orders.push_back(order);

    while (true) {
        cout << "Available Products:" << endl;
        displayProducts(); 

        int productId;
        cout << "Enter product ID to add to order (0 to finish): ";
        cin >> productId;

        if (productId == 0) break;

        bool found = false;
        for (int i = 0; i < products.size(); i++) {
            if (products[i]->getId() == productId) {
                int quantity;
                cout << "Enter quantity to order: ";
                cin >> quantity;

                if (products[i]->getQuantity() >= quantity) {
                    products[i]->reduceQuantity(quantity);
                    order->addProduct(products[i], quantity);
                    found = true;
                    break;
                } else {
                    cout << "Not enough quantity available." << endl;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "Product ID not found." << endl;
        }
    }
}
/// mehtod to say products are available or not
void Store::displayProducts() {
    if (isProductListEmpty()) {
        cout << "No products available." << endl;
        return;
    }

    for (int i = 0; i < products.size(); i++) {
        products[i]->display();
    }
}
/// mehtod to say orders are available or not
void Store::displayOrders() {
    if (isOrderListEmpty()) {
        cout << "No orders available." << endl;
        return;
    }

    for (int i = 0; i < orders.size(); i++) {
        orders[i]->display();
    }
}

#endif // STORE_CPP
