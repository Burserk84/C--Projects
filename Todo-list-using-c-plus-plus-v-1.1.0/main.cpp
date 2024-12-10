#include <iostream>
#include "class_TodoList.cpp"

using namespace std;

int main() {
    int x;
    TodoList todoList;

    do {
        cout << "......................................\n"
             << "            Todo List\n"
             << "......................................\n\n"
             << ":::::::::::::: PROGRAM MENU ::::::::::\n"
             << "1. Add New Task\n"
             << "2. Display ALL Tasks\n"
             << "3. Mark As Complete\n"
             << "4. Edit Task\n"
             << "5. Remove Task\n"
             << "0. Exit\n\n"
             << "Enter your Choice: ";
        cin >> x;

        switch (x) {
            case 1:
                todoList.newTask();
                break;

            case 2:
                todoList.displayTasks();
                break;

            case 3:
                todoList.complete();
                break;

            case 4:
                todoList.edit();
                break;

            case 5:
                todoList.remove();
                break;

            default:
                if (x != 0) {
                    cout << "Invalid choice. Please enter a valid option.\n";
                }
                break;
        }

    } while (x != 0);

    cin.ignore();
    cin.get();
    return 0;
}
