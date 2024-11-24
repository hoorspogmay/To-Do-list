 #include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Node structure for linked list (used for tasks)
struct Task 
{
    int id;
    string description;
    string deadline;
    int priority; // 1 (High) to 5 (Low)
    bool isDeleted;
    Task* next;

    // Constructor
    Task(int id, string description) 
        : id(id), description(description), deadline(""), priority(5), isDeleted(false), next(NULL) {}
};

// Class for Task Management
class TaskManager 
{
private:
    Task* head; // Head of the linked list
    int taskCount; // To assign unique IDs

public:
    TaskManager() : head(NULL), taskCount(0) {}

    // Add a new task
    void addTask(string description) 
	{
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

    // Delete a task by ID
    void deleteTask(int id) {
        if (head == NULL) {
            cout << "\n\n No tasks to delete.";
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "\n\n Task with ID " << id << " deleted successfully.";
            return;
        }

        Task* temp = head;
        Task* prev = NULL;

        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "\n\n Task with ID " << id << " not found.";
        } else {
            prev->next = temp->next;
            delete temp;
            cout << "\n\n Task with ID " << id << " deleted successfully.";
        }
    }

    // Edit a task by ID
    void editTask(int id, string newDescription) {
        Task* temp = head;
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "\n\n Task with ID " << id << " not found.";
        } else {
            temp->description = newDescription;
            cout << "\n\n Task with ID " << id << " updated successfully.";
        }
    }

    // Set a deadline for a task
    void setDeadline(int id, string deadline) {
        Task* temp = head;
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "\n\n Task with ID " << id << " not found.";
        } else {
            temp->deadline = deadline;
            cout << "\n\n Deadline for Task ID " << id << " set to: " << deadline;
        }
    }

    // Display tasks with deadlines
    void displayDeadlines() {
        if (head == NULL) {
            cout << "\n\n No tasks with deadlines.";
            return;
        }

        Task* temp = head;
        cout << "\n\n Tasks with Deadlines:";
        while (temp != NULL) {
            if (!temp->deadline.empty() && !temp->isDeleted) {
                cout << "\n ID: " << temp->id 
                     << " - " << temp->description 
                     << " | Deadline: " << temp->deadline;
            }
            temp = temp->next;
        }
    }

    // Set priority for a task
    void setPriority(int id, int priority) {
        if (priority < 1 || priority > 5) {
            cout << "\n\n Invalid priority. Please set a value between 1 (High) and 5 (Low).";
            return;
        }

        Task* temp = head;
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "\n\n Task with ID " << id << " not found.";
        } else {
            temp->priority = priority;
            cout << "\n\n Priority for Task ID " << id << " set to: " << priority;
        }
    }

    // Sort tasks by priority
    void sortTasksByPriority() {
        if (head == NULL || head->next == NULL) {
            cout << "\n\n Not enough tasks to sort.";
            return;
        }

        bool swapped;
        Task* ptr1;
        Task* lptr = NULL;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (!ptr1->isDeleted && !ptr1->next->isDeleted && ptr1->priority > ptr1->next->priority) {
                    swap(ptr1->id, ptr1->next->id);
                    swap(ptr1->description, ptr1->next->description);
                    swap(ptr1->deadline, ptr1->next->deadline);
                    swap(ptr1->priority, ptr1->next->priority);
                    swap(ptr1->isDeleted, ptr1->next->isDeleted);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "\n\n Tasks sorted by priority.";
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
            if (!temp->isDeleted) {
                cout << "\n ID: " << temp->id 
                     << " - " << temp->description 
                     << " | Deadline: " << (temp->deadline.empty() ? "N/A" : temp->deadline)
                     << " | Priority: " << temp->priority;
            }
            temp = temp->next;
        }
    }
};

// Menu display functions
void displayMainMenu() {
    cout << "\n\t*********************************************";
    cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
    cout << "\n\t*********************************************";
    cout << "\n\t*  1. Manage Tasks                          *";
    cout << "\n\t*  2. Manage Deadlines                      *";
    cout << "\n\t*  3. Manage Priorities                     *";
    cout << "\n\t*  4. Exit                                  *";
    cout << "\n\t*********************************************";
    cout << "\n\t  Enter Your Choice: "; 
}

void displayTaskMenu() {
    cout << "\n\t*********************************************";
    cout << "\n\t*            MANAGE TASKS MENU              *";
    cout << "\n\t*********************************************";
    cout << "\n\t*  1. Add Task                              *";
    cout << "\n\t*  2. Delete Task                           *";
    cout << "\n\t*  3. Edit Task                             *";
    cout << "\n\t*  4. Display Tasks                         *";
    cout << "\n\t*  5. Go Back                               *";
    cout << "\n\t*********************************************";
    cout << "\n\t  Enter Your Choice: ";
}

void displayDeadlineMenu() {
    cout << "\n\t*********************************************";
    cout << "\n\t*           MANAGE DEADLINES MENU           *";
    cout << "\n\t*********************************************";
    cout << "\n\t*  1. Add Deadline                          *";
    cout << "\n\t*  2. Edit Deadlines                        *";
    cout << "\n\t*  3. Delete Deadlines                      *";
    cout << "\n\t*  4. Notify User                           *";
    cout << "\n\t*  5. Go Back                               *";
    cout << "\n\t*********************************************";
    cout << "\n\t  Enter Your Choice: ";
}

void displayPriorityMenu() {
    cout << "\n\t*********************************************";
    cout << "\n\t*           MANAGE PRIORITIES MENU          *";
    cout << "\n\t*********************************************";
    cout << "\n\t*  1. Set Priorities                         *";
    cout << "\n\t*  2. Sort Tasks                         *";
    cout << "\n\t*  5. Go Back                               *";
    cout << "\n\t*********************************************";
    cout << "\n\t  Enter Your Choice: ";
}

// Main function
int main() 
{
    TaskManager taskManager;
    int mainChoice, subChoice, id, priority;
    char choice;
    string description, deadline;

    while (true) 
	{
        system("cls");
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice)
		 {
            case 1: // Manage Tasks
                do 
				{
                    system("cls");
                    displayTaskMenu();
                    cin >> subChoice;

                    switch (subChoice) 
					{
                        case 1: // Add Task
                            do 
							{
                                system("cls");
                                cout << "\n\t*********************************************";
                                cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                                cout << "\n\t*********************************************";
                                cout << "\n\t*                Add Task                   *";
                                cout << "\n\t*********************************************";
                                cout << "\n\nEnter Task Description: ";
                                cin.ignore();
                                getline(cin, description);
                                taskManager.addTask(description);

                                cout << "\n\n Do you want to add another task? (Y/N): ";
                                cin >> choice;
                                choice =toupper(choice );
                            } 
							while (choice=='Y');
							break;

                        case 2: // Delete Task
                            system("cls");
                            cout << "\n\t*********************************************";
                            cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                            cout << "\n\t*********************************************";
                            cout << "\n\t*             Delete Task                   *";
                            cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            cout << "\n\n Enter Task ID to delete: ";
                            cin >> id;
                            taskManager.deleteTask(id);
                            system("pause");
                            break;

                        case 3: // Edit Task
                            system("cls");
                            cout << "\n\t*********************************************";
                            cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                            cout << "\n\t*********************************************";
                            cout << "\n\t*             Edit Task                     *";
                            cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            cout << "\n\n Enter Task ID to edit: ";
                            cin >> id;
                            cout << "Enter new description: ";
                            cin.ignore();
                            getline(cin, description);
                            taskManager.editTask(id, description);
                            system("pause");
                            break;

                        case 4: // Display Tasks
                            system("cls");
                            cout << "\n\t*********************************************";
                            cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                            cout << "\n\t*********************************************";
                            cout << "\n\t*             Display Task                  *";
                            cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            system("pause");
                            break;

                        case 5: // Go Back
                            break;

                        default:
                            cout << "\n\n Invalid choice. Try again.";
                            system("pause");
                    }
                } 
				while (subChoice != 5);
                break;

            case 2: // Manage Deadlines
                do
				 {
                    system("cls");
                    displayDeadlineMenu();
                    cin >> subChoice;

                    switch (subChoice) 
					{
                        case 1: // Add Deadline
                            system("cls");
                            cout << "\n\t*********************************************";
                            cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                            cout << "\n\t*********************************************";
                            cout << "\n\t*             Add Deadline                  *";
                            cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            cout << "\n\n Enter Task ID to set deadline: ";
                            cin >> id;
                            cout << "Enter deadline (YYYY-MM-DD): ";
                            cin.ignore();
                            getline(cin, deadline);
                            taskManager.setDeadline(id, deadline);
                            system("pause");
                            break;

                        case 2: // Edit Deadline
                            system("cls");
                            cout << "\n\t*********************************************";
                            cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                            cout << "\n\t*********************************************";
                            cout << "\n\t*             Edit Deadline                 *";
                            cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            cout << "\n\n Enter Task ID to edit deadline: ";
                            cin >> id;
                            cout << "Enter new deadline (YYYY-MM-DD): ";
                            cin.ignore();
                            getline(cin, deadline);
                            taskManager.setDeadline(id, deadline);
                            system("pause");
                            break;

                        case 3: // Delete Deadlines (optional feature placeholder)
                        do 
						{
                    system("cls");
                    cout << "\n\t*********************************************";
                    cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                    cout << "\n\t*********************************************";
                    cout << "\n\t*             Delete Deadline               *";
                    cout << "\n\t*********************************************";
                    cout << "\n\n Enter Task ID to Delete Deadline: ";
                    cin >> id;

                    // Deleting a deadline means setting it to an empty string
                    taskManager.setDeadline(id, "");

                    cout << "\n\n Deadline for Task ID " << id << " has been deleted.";
                    cout << "\n\n Do you want to delete another deadline? (Y/N): ";
                    cin >> choice;
                } 
				while (choice == 'Y' || choice == 'y');
                break;
                case 4: // Notify User (placeholder)
                            system("cls");
                     cout << "\n\t*********************************************";
                     cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                     cout << "\n\t*********************************************";
                     cout << "\n\t*        DEADLINE NOTIFICATIONS             *";
                     cout << "\n\t*********************************************\n";
                     taskManager.displayDeadlines();
                     break;

                        case 5: // Go Back
                        break;

                        default:
                            cout << "\n\n Invalid choice. Try again.";
                            system("pause");
                    }
                } 
				while (subChoice != 5);
                break;

            case 3: // Manage Priorities
                do
				 {
                    system("cls");
                    displayPriorityMenu();
                    cin >> subChoice;

                    switch (subChoice) 
					{
                        case 1: // Set Priority
                            system("cls");
                    cout << "\n\t*********************************************";
                    cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                    cout << "\n\t*********************************************";
                    cout << "\n\t*             Set Priorities                *";
                    cout << "\n\t*********************************************";
                            taskManager.displayTasks();
                            cout << "\n\n Enter Task ID to set priority: ";
                            cin >> id;
                            cout << "Enter priority (1-5): ";
                            cin >> priority;
                            taskManager.setPriority(id, priority);
                            system("pause");
                            break;

                        case 2: // Sort Tasks
                            system("cls");
                        cout << "\n\t*********************************************";
                        cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
                        cout << "\n\t*********************************************";
                        cout << "\n\t*             Sort Tasks                    *";
                        cout << "\n\t*********************************************";
                            taskManager.sortTasksByPriority();
                            system("pause");
                            break;

                        case 5: // Go Back
                            break;

                        default:
                            cout << "\n\n Invalid choice. Try again.";
                            system("pause");
                    }
                } 
				while (subChoice != 5);
                break;

            case 4: // Exit
                cout << "\n\n Exiting the system. Thank you!";
                return 0;

            default:
                cout << "\n\n Invalid choice. Try again.";
                system("pause");
        }
    }
    return 0;
}

