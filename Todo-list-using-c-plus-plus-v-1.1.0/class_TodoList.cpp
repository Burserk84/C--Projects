#include <string>
#include <fstream>
#include "Vector.cpp"

using namespace std;

void clearscrean() {
    system("cls");
}

const string FILENAME = "tasks.txt";

// Function to check if a date string is in valid format (YYYY-MM-DD)
bool isValidDateFormat(const string& date) {
    if (date.length() != 10) // Check if the length is exactly 10 characters
        return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (date[i] != '-' && date[i] != '/') // Check if the separators are at the correct positions
                return false;
        } else {
            if (!isdigit(date[i])) // Check if all other characters are digits
                return false;
        }
    }
    return true;
}

// Function to validate date values
bool isValidDate(const string& date) {
    int year, month, day;
    string yearStr = date.substr(0, 4);
    string monthStr = date.substr(5, 2);
    string dayStr = date.substr(8, 2);

    try {
        year = stoi(yearStr);
        month = stoi(monthStr);
        day = stoi(dayStr);
    } catch (const invalid_argument& e) {
        return false; // stoi failed, not all characters are digits
    } catch (const out_of_range& e) {
        return false; // stoi failed, value out of range
    }

    if (year < 0)
        return false; // Year must be non-negative
    if (month < 1 || month > 12)
        return false; // Month must be between 1 and 12
    if (day < 1 || day > 31)
        return false; // Day must be between 1 and 31
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false; // April, June, September, and November have 30 days
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29)
                return false; // February has 29 days in a leap year
        } else {
            if (day > 28)
                return false; // February has 28 days in a non-leap year
        }
    }
    return true;
}

class TodoList {
private:
    Vector<string> tasks;

//////////// Load tasks from file/////////////////
    void loadTasks() {
        ifstream inFile(FILENAME);
        if (inFile.is_open()) {
            string task;
            while (getline(inFile, task)) {
                tasks.push_back(task);
            }
            inFile.close();
        }
    }

////////////// Save tasks to file/////////////////
    void saveTasks() {
        ofstream outFile(FILENAME);
        if (outFile.is_open()) {
            for (int i = 0; i < tasks.getSize(); ++i) {
                outFile << tasks[i] << endl;
            }
            outFile.close();
        }
    }

public:
//////// Constructor: load tasks from file///////
    TodoList() {
        loadTasks();
    }

/////////////// Add a new task/////////////////
    void newTask() {
        clearscrean();
        cout << "......................................\n"
             << "            Todo List\n"
             << "......................................\n\n"
             << ":::::::::::::: New Task ::::::::::\n";

        string text;
        string date;
        cout << "Enter the task: ";
        cin.ignore();
        getline(cin, text);
        
        while (true) {
        cout << "Set the time (YYYY-MM-DD): ";
        getline(cin, date);

        if (isValidDateFormat(date) && isValidDate(date))
            break;
        else
            cout << "Invalid date format or value! Please use YYYY-MM-DD and enter a valid date.\n";
        }

        string taskWithDate = text + " " + date;
        tasks.push_back(taskWithDate);
        saveTasks();
        cout << "Task added successfully!\n";
        cout << "\nPress Enter to go to menu";
        cin.ignore();
    }

/////////////// Display all tasks///////////////
    void displayTasks() {
        clearscrean();
        cout << ":::::::::::::: Tasks ::::::::::\n";
        for (int i = 0; i < tasks.getSize(); ++i) {
            cout << i << ". " << tasks[i] << endl;
        }
    }

//////////// Mark a task as complete///////////
    void complete() {
        clearscrean();
        cout << "......................................\n"
             << "            Todo List\n"
             << "......................................\n\n"
             << ":::::::::::::: Complete ::::::::::\n";

        int index;
        displayTasks();
        cout << "Enter the index of the task to mark as complete:(start from 0) ";
        cin >> index;

        if (index >= 0 && index < tasks.getSize()) {
            tasks[index] = "[Complete] " + tasks[index];
            saveTasks();
            cout << "Task marked as complete!\n";
        } else {
            cout << "Invalid index!\n";
        }
    }

/////////////// Edit a task///////////////////
    void edit() {
        clearscrean();
        string date;
        cout << "......................................\n"
             << "            Todo List\n"
             << "......................................\n\n"
             << ":::::::::::::: Edit ::::::::::\n";

        int index;
        displayTasks();
        cout << "Enter the index of the task to edit:(start from 0) ";
        cin >> index;

        if (index >= 0 && index < tasks.getSize()) {
            cout << "Enter the new task: ";
            cin.ignore();
            getline(cin, tasks[index]);

            while (true) {
                cout << "Set the time (YYYY-MM-DD): ";
                getline(cin, date);

                if (isValidDateFormat(date) && isValidDate(date))
                    break;
                else
                    cout << "Invalid date format or value! Please use YYYY-MM-DD and enter a valid date.\n";
            }   

            tasks[index] = tasks[index] + " " + date;
            saveTasks();
            cout << "Task edited successfully!\n";
        } else {
            cout << "Invalid index!\n";
        }

        cout << "\nPress Enter to go to menu";
        cin.ignore();
    }

/////////////// Remove a task////////////////
    void remove() {
        clearscrean();
        cout << "......................................\n"
             << "            Todo List\n"
             << "......................................\n\n"
             << ":::::::::::::: Remove ::::::::::\n";

        int index;
        displayTasks();
        cout << "Enter the index of the task to remove:(start from 0) ";
        cin >> index;

        if (index >= 0 && index < tasks.getSize()) {
            tasks.erase(index);
            saveTasks();
            cout << "Task removed successfully!\n";
        } else {
            cout << "Invalid index!\n";
        }
    }
};
