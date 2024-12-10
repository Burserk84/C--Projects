#include <iostream>
#include <cstdlib>
#include <limits>
#include "Store.cpp"

using namespace std;

bool getInputInt(int &input) {
    cin >> input;
    if (cin.fail() || input < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number." << endl;
        return false;
    }
    return true;
}

bool getInputDouble(double &input) {
    cin >> input;
    if (cin.fail() || input < 0.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid positive price." << endl;
        return false;
    }
    return true;
}

bool getInputString(string &input) {
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid string." << endl;
        return false;
    }
    return true;
}

int main() {
    Store store;
    char choice;

    while (true) {
        system("cls");
        cout << "Menu:\n1. Add New Product\n2. Display All Products\n3. Create New Order\n4. Display All Orders\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                int type;
                cout << "Enter product type (1 for Perishable, 2 for ImPerishable): ";
                if (!getInputInt(type) || (type != 1 && type != 2)) {
                    cout << "Invalid product type." << endl;
                    break;
                }

                int id, quantity;
                string name;
                double price;

                while (true) {
                    cout << "Enter product ID: ";
                    if (!getInputInt(id)) break;
                    if (id == 0 || !store.isProductIdUnique(id)) {
                        cout << "Product ID must be unique and greater than 0." << endl;
                        continue;
                    }
                    break;
                }

                cout << "Enter product name: ";
                if (!getInputString(name)) break;
                cout << "Enter product price: ";
                if (!getInputDouble(price)) break;
                cout << "Enter product quantity: ";
                if (!getInputInt(quantity)) break;

                if (type == 1) {
                    string expirationDate;
                    while (true) {
                        cout << "Enter expiration date (YYYY-MM-DD): ";
                        if (!getInputString(expirationDate)) break;
                        if (!PerishableProduct::isValidDate(expirationDate)) {
                            cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
                            continue;
                        }
                        break;
                    }
                    store.addProduct(new PerishableProduct(id, name, price, quantity, expirationDate));
                } else if (type == 2) {
                    store.addProduct(new ImPerishableProduct(id, name, price, quantity));
                }
                break;
            }
            case '2':
                store.displayProducts();
                break;
            case '3':
                store.createOrder();
                break;
            case '4':
                store.displayOrders();
                break;
            case '5':
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        system("pause");
    }
}
