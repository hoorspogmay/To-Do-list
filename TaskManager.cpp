#include <iostream>
#include <string>

using namespace std;

// Node structure for linked list
struct Task {
    int id;
    string description;
    Task* next;

    // Constructor
    Task(int id, string description) : id(id), description(description), next(nullptr) {}
};

// Class for Task Management
class TaskManager {
private:
    Task* head; // Head of the linked list
    int taskCount; // To assign unique IDs

public:
    TaskManager() : head(nullptr), taskCount(0) {}

    // Add a new task
    void addTask(string description) {
        Task* newTask = new Task(++taskCount, description);
        if (head == nullptr) {
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newTask;
        }
        cout << "Task added successfully with ID: " << taskCount << endl;
    }

    // Remove a task by ID
    void removeTask(int id) {
        if (head == nullptr) {
            cout << "No tasks to remove." << endl;
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << id << " removed successfully." << endl;
            return;
        }

        Task* temp = head;
        Task* prev = nullptr;

        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Task with ID " << id << " not found." << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Task with ID " << id << " removed successfully." << endl;
    }

    // Display all tasks
    void displayTasks() {
        if (head == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }

        Task* temp = head;
        cout << "Your To-Do List:" << endl;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " - " << temp->description << endl;
            temp = temp->next;
        }
    }

    // Destructor to clean up memory
    ~TaskManager() {
        while (head != nullptr) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function
int main() {
    TaskManager taskManager;
    int choice;
    string description;
    int id;

    do {
        cout << "\n--- Task Management System ---\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. View Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore(); // Clear the input buffer
                cout << "Enter task description: ";
                getline(cin, description);
                taskManager.addTask(description);
                break;
            case 2:
                cout << "Enter task ID to remove: ";
                cin >> id;
                taskManager.removeTask(id);
                break;
            case 3:
                taskManager.displayTasks();
                break;
            case 4:
                cout << "Exiting Task Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
