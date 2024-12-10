#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

const string FILENAME = "tasks.txt";

void clearscrean() {
    system("cls");
}

void loadTasks(vector<string>& tasks) {
	
    ifstream inFile(FILENAME);
    
	if (inFile.is_open()) {
    
	    string task;
    
	    while (getline(inFile, task)) {
    
	        tasks.push_back(task);
    
	    }
    
	    inFile.close();
    
	}
}

void saveTasks(const vector<string>& tasks) {
    
	ofstream outFile(FILENAME);
    
	if (outFile.is_open()) {
    
	    for (const string& task : tasks) {
    
	        outFile << task << endl;
    
	    }
    
	    outFile.close();
    
	}
}

void newTask(vector<string>& tasks) {
    
	clearscrean();
    
	cout << "......................................\n"
         << "            Todo List\n"
         << "......................................\n\n"
         << ":::::::::::::: New Task ::::::::::\n";

    string text;
    
	cout << "Enter the task for today: ";
    
	cin.ignore();
    
	getline(cin, text);
    
	tasks.push_back(text);
    
	saveTasks(tasks);
    
	cout << "Task added successfully!\n";

    cout << "\nPress Enter to go to menu";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayTasks(const vector<string>& tasks) {
    
	clearscrean();
    
	cout << ":::::::::::::: Tasks ::::::::::\n";

    for (int i = 0; i < tasks.size(); ++i) {
        cout << i << ". " << tasks[i] << endl;
    }
}

void complete(vector<string>& tasks) {
    
	clearscrean();
    
	cout << "......................................\n"
         << "            Todo List\n"
         << "......................................\n\n"
         << ":::::::::::::: Complete ::::::::::\n";

    int index;
    
	displayTasks(tasks);
    
	cout << "Enter the index of the task to mark as complete:(start from 0) ";
    
	cin >> index;

    if (index >= 0 && index < tasks.size()) {
    
	    tasks[index] = "[Complete] " + tasks[index];
    
	    saveTasks(tasks);
    
	    cout << "Task marked as complete!\n";
    }
    else {
    
	    cout << "Invalid index!\n";
    
	}
}

void edit(vector<string>& tasks) {
    
	clearscrean();
    
	cout << "......................................\n"
         << "            Todo List\n"
         << "......................................\n\n"
         << ":::::::::::::: Edit ::::::::::\n";

    int index;
    
	displayTasks(tasks);
    
	cout << "Enter the index of the task to edit:(start from 0) ";
    
	cin >> index;

    if (index >= 0 && index < tasks.size()) {
    
	    cout << "Enter the new task: ";
        cin.ignore();
        getline(cin, tasks[index]);
        saveTasks(tasks);
        cout << "Task edited successfully!\n";
    
	}else {
       
	    cout << "Invalid index!\n";
    
	}

    cout << "\nPress Enter to go to menu";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void remove(vector<string>& tasks) {
    
	clearscrean();
    
	cout << "......................................\n"
         << "            Todo List\n"
         << "......................................\n\n"
         << ":::::::::::::: Remove ::::::::::\n";

    int index;
    displayTasks(tasks);
    cout << "Enter the index of the task to remove:(start from 0) ";
    cin >> index;

    if (index >= 0 && index < tasks.size()) {
    
	    tasks.erase(tasks.begin() + index);
        saveTasks(tasks);
        cout << "Task removed successfully!\n";
    
	}else {
     
	    cout << "Invalid index!\n";
    
	}
}

int main() {
    
	int x;
    
	vector<string> tasks;

    loadTasks(tasks);

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
            newTask(tasks);
            break;

        case 2:
            displayTasks(tasks);
            break;

        case 3:
            complete(tasks);
            break;

        case 4:
            edit(tasks);
            break;

        case 5:
            remove(tasks);
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
