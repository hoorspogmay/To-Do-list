#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// Node structure for linked list
struct Task {
    int id;
    string description;
    Task* next;

    // Constructor
    Task(int id, string description) : id(id), description(description), next(NULL) {}
};

// Class for Task Management
class TaskManager {
private:
    Task* head; // Head of the linked list
    int taskCount; // To assign unique IDs

public:
    TaskManager() : head(NULL), taskCount(0) {}

    // Add a new task
    void addTask(string description) {
        Task* newTask = new Task(++taskCount, description);
        if (head == NULL) {
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newTask;
        }
        cout << "\n\n Task added successfully with ID: " << taskCount;
    }

    // Remove a task by ID
    void removeTask(int id) {
        if (head == NULL) {
            cout << "\n\n No tasks to remove.";
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "\n\n Task with ID " << id << " removed successfully.";
            return;
        }

        Task* temp = head;
        Task* prev = NULL;

        while (temp != NULL&& temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "\n\n Task with ID " << id << " not found.";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "\n\n Task with ID " << id << " removed successfully.";
    }

    // Display all tasks
    void displayTasks() {
        if (head == NULL) {
            cout << "\n\n No tasks to display.";
            return;
        }

        Task* temp = head;
        cout << "\n\n Your To-Do List:";
        while (temp != NULL) {
            cout << "\n ID: " << temp->id << " - " << temp->description;
            temp = temp->next;
        }
    }

    // Destructor to clean up memory
    ~TaskManager() {
        while (head != NULL) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Function to display control panel
void control_panel()
{

  cout << "\n---------------------------------------------";
    cout << "\n*                                           *";
    cout << "\n*        TASK MANAGEMENT SYSTEM             *";
    cout << "\n*                                           *";
    cout << "\n---------------------------------------------";
    cout << "\n*                                           *";
    cout << "\n*  1. Add Task                              *";
    cout << "\n*  2. Remove Task                           *";
    cout << "\n*  3. View Tasks                            *";
    cout << "\n*  4. Exit                                  *";
    cout << "\n*                                           *";
    cout << "\n---------------------------------------------";
    cout << "\n Enter Your Choice: ";
}

// Main function
int main() {
    TaskManager taskManager;
    int choice;
    string description;
    int id;
    char x;

p:
    system("cls");
    control_panel();
    cin >> choice;
    switch (choice) {
        case 1:
            do {
                system("cls");
                cout << "\n\n\t\t\t  Task Management System";
                cout << "\n\n\n\t\t\t\tAdd Task";
                cout << "\n\n Enter Task Description: ";
                cin.ignore();
                getline(cin, description);
                taskManager.addTask(description);
                cout << "\n\n Do You Want To Add Another Task (y/n)? ";
                cin >> x;
            } while (x == 'y');
            break;
        case 2:
            do {
                system("cls");
                cout << "\n\n\t\t\t  Task Management System";
                cout << "\n\n\n\t\t\t\tRemove Task";
                cout << "\n\n Enter Task ID to Remove: ";
                cin >> id;
                taskManager.removeTask(id);
                cout << "\n\n Do You Want To Remove Another Task (y/n)? ";
                cin >> x;
            } while (x == 'y');
            break;
        case 3:
            system("cls");
            cout << "\n\n\t\t\t  Task Management System";
            cout << "\n\n\n\t\t\t\tView Tasks";
            taskManager.displayTasks();
            cout << "\n\n Press any key to go back...";
            getch();
            break;
        case 4:
            exit(0);
        default:
            cout << "\n\n Invalid Choice. Please Try Again.";
            getch();
    }
    goto p;

    return 0;
}
