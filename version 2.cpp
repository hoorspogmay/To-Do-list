#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Node structure for linked list (used for tasks)
struct Task {
	int id;
	string description;
	string deadline;
	int priority; // 1 (High) to 5 (Low)
	string category; // Work, Personal, Study, etc.
	string status; // Pending, In Progress, Completed
	string estimatedDuration; // Estimated time in minutes
	bool isDeleted;
	Task* next;

	// Constructor
	Task(int id, string description) {
		this->id = id;
		this->description = description;
		this->deadline = "";
		this->priority = 0;
		this->category = "Uncategorized";
		this->status = "Pending";
		this->estimatedDuration = "N/A";
		this->isDeleted = false;
		this->next = NULL;
	}

};

class TaskManager {
	private:
		Task* head;
		int taskCount;
		const char* filename = "tasks.txt";

	public:
		TaskManager() {
			head = NULL;
			taskCount = 0;
		}


		// Add a new task
		void addTask(string description, string category, string estimatedDuration) {

			if (description.empty()) {
				cout << "Description cannot be empty." << endl;
				return;
			}

			if (category != "Work" && category != "Personal" && category != "Study" && category != "Other" &&
			        category != "work" && category != "personal" && category != "study" && category != "other") {
				cout << "Invalid category. Please choose from Work, Personal, Study, or Other." << endl;
				return;
			}
			int duration;
			try {
				duration = stoi(estimatedDuration);
				if (duration < 0) {
					cout << "Estimated duration cannot be negative." << endl;
					return;
				}
			} catch (invalid_argument&) {
				cout << "Invalid estimated duration. Please enter a valid number." << endl;
				return;
			} catch (out_of_range&) {
				cout << "Estimated duration is too large. Please enter a smaller number." << endl;
				return;
			}

			Task* newTask = new Task(++taskCount, description);
			newTask->category = category;
			newTask->estimatedDuration = estimatedDuration;

			if (head == NULL) {
				head = newTask;
			} else {
				Task* temp = head;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newTask;
			}

			cout << "\n\nTask added successfully with ID: " << taskCount << endl; // Confirmation message
		}

		void deleteTask(int id) {
			if (head == NULL) {
				cout << "\n\n No tasks to delete.";
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
			}

			char confirm;
			cout << "\n\n Are you sure you want to delete Task ID " << id << "? (Y/N): ";
			cin >> confirm;
			confirm = toupper(confirm);

			if (confirm != 'Y') {
				cout << "\n\n Deletion cancelled." << endl;
				return;
			}
			if (head->id == id) {
				Task* temp = head;
				head = head->next;
				delete temp;
				cout << "\n\n Task with ID " << id << " deleted successfully.";
				return;
			}

			while (temp != NULL && temp->id != id) {
				prev = temp;
				temp = temp->next;
			}

			if (temp != NULL) {
				prev->next = temp->next;
				delete temp;
				cout << "\n\n Task with ID " << id << " deleted successfully." << endl;
			}
		}

// Edit a task by ID
		void editTask(int id) {
			Task* temp = head;

			// Check if task exists
			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}

			if (temp == NULL) {
				cout << "\n\n Task with ID " << id << " not found.";
				return;
			}

			int choice;
			cout << "\n\n Task with ID " << id << " found:";
			cout << "\n Description: " << temp->description;
			cout << "\n Category: " << temp->category;
			cout << "\n Status: " << temp->status;
			cout << "\n Estimated Duration: " << temp->estimatedDuration;

			cout << "\n\n What do you want to edit?";
			cout << "\n 1. Description";
			cout << "\n 2. Category";
			cout << "\n 3. Status";
			cout << "\n 4. Estimated Duration";
			cout << "\n Enter your choice: ";
			cin >> choice;
			cin.ignore();

			switch (choice) {
				case 1: {
					string newDescription;
					cout << "\n Enter new description: ";
					getline(cin, newDescription);
					if(newDescription == "") {
						cout<<"\nDescription field empty";
						break;
					} else {
						temp->description = newDescription;
						cout << "\n Description updated successfully.";
						break;
					}
				}
				case 2: {
					string newCategory;
					cout << "\n Enter new category: ";
					getline(cin, newCategory);

					if (newCategory != "Work" && newCategory != "Personal" && newCategory != "Study" && newCategory != "Other" &&
					        newCategory != "work" && newCategory != "personal" && newCategory != "study" && newCategory != "other") {
						cout << "Invalid category. Please choose from Work, Personal, Study, or Other." << endl;
						break;
					} else {
						temp->category = newCategory;
						cout << "\n Category updated successfully.";
						break;
					}
				}
				case 3: {
					string newStatus;
					cout << "\n Enter new status: ";
					getline(cin, newStatus);

					temp->status = newStatus;
					cout << "\n Status updated successfully.";
					break;
				}
				case 4: {
					string newDuration;
					cout << "\n Enter new estimated duration: ";
					getline(cin, newDuration);
					temp->estimatedDuration = newDuration;
					cout << "\n Estimated duration updated successfully.";
					break;
				}
				default:
					cout << "\n Invalid choice.";
			}
		}


// Set a deadline for a task
		void setDeadline(int id) {
			Task* temp = head;

			// Search for the task by ID
			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}

			if (temp == NULL) {
				// Task not found
				cout << "\n\n Task with ID " << id << " not found. No deadline can be set.";
				return;
			}
			cout << "\n Task with ID " << id << " found: " << temp->description;
			cout << "\n Enter deadline (YYYY-MM-DD): ";
			string deadline;
			cin.ignore();
			getline(cin, deadline);

			temp->deadline = deadline;
			cout << "\n\n Deadline for Task ID " << id << " set to: " << deadline;
		}


// Edit deadline
		void editDeadline(int id) {
			Task* temp = head;

			// Search for the task by ID
			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}

			if (temp == NULL) {
				// Task not found
				cout << "\n\n Task with ID " << id << " not found. No deadline can be edited.";
				return;
			}

			// Task found, prompt for new deadline
			cout << "\n Task with ID " << id << " found: " << temp->description;
			cout << "\n Enter new deadline (YYYY-MM-DD): ";
			string newDeadline;
			cin.ignore();
			getline(cin, newDeadline);

			// Set the new deadline
			temp->deadline = newDeadline;
			cout << "\n\n Deadline for Task ID " << id << " updated to: " << newDeadline;
		}



// delete a deadline
		void deleteDeadline(int id) {
			Task* temp = head;
			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}
			if (temp == NULL) {
				cout << "\n\n Task with ID " << id << " not found. No deadline to delete.";
			} else {
				temp->deadline = "N/A";  // Marking as "No Deadline"
				cout << "\n\n Deadline for Task ID " << id << " has been deleted.";
			}
		}

		// Display tasks with deadlines
		void displayDeadlines() {
			if (head == NULL) {
				cout << "\n\n No tasks with deadlines.";
				return;
			}

			Task* temp = head;
			cout << "\n\n Pending Tasks with Deadlines:";
			bool found = false;
			while (temp != NULL) {
				if (!temp->deadline.empty() && temp->status == "Pending" && !temp->isDeleted) {
					cout << "\n ID: " << temp->id
					     << " - " << temp->description
					     << " | Deadline: " << temp->deadline;
					found = true;
				}
				temp = temp->next;
			}

			if (!found) {
				cout << "\n\n No pending tasks with deadlines.";
			}
		}
//notifyuser
		void notifyUser() {
			system("cls");
			cout << "\n\t*********************************************";
			cout << "\n\t*        DEADLINE NOTIFICATIONS             *";
			cout << "\n\t*********************************************";
			displayDeadlines();
			cout<<"\n";
			system("pause");
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
			cout << "\n ID  | Description        | Category | Status       | Duration | Deadline       | Priority";
			cout << "\n -----------------------------------------------------------------------------";

			while (temp != NULL) {
				if (!temp->isDeleted) {
					cout << "\n " << setw(4) << temp->id
					     << " | " << setw(17) << temp->description
					     << " | " << setw(9) << temp->category
					     << " | " << setw(12) << temp->status
					     << " | " << setw(8) << temp->estimatedDuration
					     << " | " << setw(14) << (temp->deadline.empty() ? "N/A" : temp->deadline)
					     << " | " << temp->priority;
				}
				temp = temp->next;
			}
			cout << endl;
		}
		void updateStatus(int id, string Status) {
			Task* temp = head;
			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}
			if (temp == NULL) {
				cout << "\n\n Task with ID " << id << " not found.";
			} else {
				temp->status = Status;
				cout << "\n Status updated successfully.";
			}
		}
		void addToFile(int id)
		 {
			Task* temp = head;

			while (temp != NULL && temp->id != id) {
				temp = temp->next;
			}

			if (temp == NULL) {
				cout << "\n\n Task with ID " << id << " not found. Cannot add to file.";
				return;
			}

			ofstream outFile(filename, ios::app);
			if (!outFile) {
				cout << "Error opening file for writing!" << endl;
				return;
			}

			outFile << temp->id << ","
			        << temp->description << ","
			        << temp->category << ","
			        << temp->estimatedDuration << ","
			        << temp->status << ","
			        << temp->deadline << ","
			        << temp->priority << endl;

			outFile.close();
			cout << "\n\n Task with ID " << id << " added to file successfully." << endl;
		}

		void displayFile() {
			ifstream inFile(filename);
			if (!inFile) {
				cout << "Error opening file for reading!" << endl;
				return;
			}

			string line;
			cout << "\n\n Tasks in file:" << endl;
			while (getline(inFile, line)) {
				cout << line << endl; 
			}
			inFile.close();
		}

		void clearFile() {
			ofstream outFile(filename, ios::trunc); 
			if (!outFile) {
				cout << "Error opening file for clearing!" << endl;
				return;
			}
			outFile.close(); 
			cout << "File cleared successfully." << endl;
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
	cout << "\n\t*  4. Manage Status                         *";
	cout << "\n\t*  5. Manage File                           *";
	cout << "\n\t*  6. Exit                                  *";
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
	cout << "\n\t*  1. Set Deadline                          *";
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
	cout << "\n\t*  2. Sort Tasks                             *";
	cout << "\n\t*  5. Go Back                                *";
	cout << "\n\t*********************************************";
	cout << "\n\t  Enter Your Choice: ";
}
void displayStatusMenu() {
	cout << "\n\t*********************************************";
	cout << "\n\t*            MANAGE STATUS MENU             *";
	cout << "\n\t*********************************************";
	cout << "\n\t*  1. Update Status                         *";
	cout << "\n\t*  2. Display Status                        *";
	cout << "\n\t*  3. Go Back                               *";
	cout << "\n\t*********************************************";
	cout << "\n\t  Enter Your Choice: ";
}
void displayFileMenu() {
	cout << "\n\t*********************************************";
	cout << "\n\t*            MANAGE FILE MENU               *";
	cout << "\n\t*********************************************";
	cout << "\n\t*  1. Add to file                           *";
	cout << "\n\t*  2. Display file contents                 *";
	cout << "\n\t*  3. Clear File                            *";
	cout << "\n\t*  4. Go Back                               *";
	cout << "\n\t*********************************************";
	cout << "\n\t  Enter Your Choice: ";
}

// Main function
int main() {
	TaskManager taskManager;
	int mainChoice, subChoice, id, priority;
	char choice;
	string description, deadline,category,status,estimatedDuration;

	while (true) {
		system("cls");
		displayMainMenu();
		cin >> mainChoice;

		switch (mainChoice) {
			case 1: // Manage Tasks
				do {
					system("cls");
					displayTaskMenu();
					cin >> subChoice;

					switch (subChoice) {
						case 1: // Add Task
							do {
								system("cls");
								cout << "\n\t*********************************************";
								cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
								cout << "\n\t*********************************************";
								cout << "\n\t*                Add Task                   *";
								cout << "\n\t*********************************************";
								cout << "\n\nEnter Task Description: ";
								cin.ignore();
								getline(cin, description);
								cout << "Enter Task Category (Work, Personal, Study, etc.): ";
								getline(cin, category);
								cout << "Enter Estimated Duration: ";
								cin >> estimatedDuration;
								taskManager.addTask(description, category, estimatedDuration);

								cout << "\n\n Do you want to add another task? (Y/N): \n";
								cin >> choice;
								choice =toupper(choice );
							} while (choice=='Y');
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
							cout<<"\n";
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
							taskManager.editTask(id);
							cout<<"\n";
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
							cout<<"\n";
							system("pause");
							break;

						case 5: // Go Back
							break;

						default:
							cout << "\n\n Invalid choice. Try again.\n";
							system("pause");
					}
				} while (subChoice != 5);
				break;

			case 2: // Manage Deadlines
				do {
					system("cls");
					displayDeadlineMenu();
					cin >> subChoice;

					switch (subChoice) {
						case 1: // Set Deadline
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Set Deadline                  *";
							cout << "\n\t*********************************************";
							taskManager.displayTasks();
							cout << "\n\n Enter Task ID to set deadline: \n";
							cin >> id;

							taskManager.setDeadline(id);  // Now we call setDeadline without passing the deadline in main function
							cout<<"\n";
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
							cout << "\n\n Enter Task ID to edit deadline: \n";
							cin >> id;

							taskManager.setDeadline(id);
							cout<<"\n";
							system("pause");
							break;

						case 3: // Delete Deadline
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*           Delete Deadline                 *";
							cout << "\n\t*********************************************";
							taskManager.displayTasks();
							cout << "\n\n Enter Task ID to delete deadline: ";
							cin >> id;
							taskManager.deleteDeadline(id);
							cout<<"\n";
							system("pause");
							break;

						case 4: // Notify User
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*        DEADLINE NOTIFICATIONS             *";
							cout << "\n\t*********************************************";

							system("cls");
							taskManager.notifyUser();
							cout<<"\n";
							break;

						case 5: // Go Back
							cout<<"\n";
							break;

						default:
							cout << "\n\n Invalid choice. Try again.";
							cout<<"\n";
							system("pause");
					}
				} while (subChoice != 5);
				break;

			case 3: // Manage Priorities
				do {
					system("cls");
					displayPriorityMenu();
					cin >> subChoice;

					switch (subChoice) {
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
							cout<<"\n";
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
							cout<<"\n";
							system("pause");
							break;

						case 5: // Go Back
							cout<<"\n";
							break;

						default:
							cout << "\n\n Invalid choice. Try again.";
							cout<<"\n";
							system("pause");
					}
				} while (subChoice != 5);
				break;

			case 4: // Manage Status
				do {
					system("cls");
					displayStatusMenu();
					cin >> subChoice;

					switch (subChoice) {
						case 1: // Set Status
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Update Status                 *";
							cout << "\n\t*********************************************";
							taskManager.displayTasks();
							cout << "\n\n Enter Task ID to update status: ";
							cin >> id;
							cout << "Enter status (Incomplete, Inprogress, Complete): ";
							cin >> status;
							taskManager.updateStatus(id, status);
							cout<<"\n";
							system("pause");
							break;

						case 2: // Display Status
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Display Status                *";
							cout << "\n\t*********************************************";
							taskManager.displayTasks();
							cout<<"\n";
							system("pause");
							break;

						case 3: // Go Back
							cout<<"\n";
							break;

						default:
							cout << "\n\n Invalid choice. Try again.";
							cout<<"\n";
							system("pause");
					}
				} while (subChoice != 5);
				break;

			case 5: // Manage File
				do {
					system("cls");
					displayFileMenu();
					cin >> subChoice;

					switch (subChoice) {
						case 1: // Add to file
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Add to file                   *";
							cout << "\n\t*********************************************";
							taskManager.displayTasks();
							cout << "\n\n Enter Task ID to add to file: ";
							cin >> id;
							taskManager.addToFile(id);
							cout<<"\n";
							system("pause");
							break;

						case 2: // Display from file
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Display File Contents         *";
							cout << "\n\t*********************************************";
							taskManager.displayFile();
							cout<<"\n";
							system("pause");
							break;

						case 3: // Clear File
							system("cls");
							cout << "\n\t*********************************************";
							cout << "\n\t*           TASK MANAGEMENT SYSTEM          *";
							cout << "\n\t*********************************************";
							cout << "\n\t*             Clear File Contents           *";
							cout << "\n\t*********************************************";
							taskManager.clearFile();
							cout<<"\n";
							system("pause");
							break;

						case 4: // Go Back
							cout<<"\n";
							break;

						default:
							cout << "\n\n Invalid choice. Try again.";
							cout<<"\n";
							system("pause");
					}
				} while (subChoice != 5);
				break;

			case 6: // Exit
				cout << "\n\n Exiting the system. Thank you!";
				return 0;

			default:
				cout << "\n\n Invalid choice. Try again.";
				cout<<"\n";
				system("pause");
		}
	}
	return 0;
}
