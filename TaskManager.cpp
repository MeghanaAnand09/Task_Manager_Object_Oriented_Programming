#include <iostream>
#include <vector>
#include <string>

class TaskBase {
protected:
    std::string description;
    std::string dueDate;
    bool isCompleted;

public:
    TaskBase(const std::string& desc, const std::string& date)
        : description(desc), dueDate(date), isCompleted(false) {}

    void markAsCompleted() {
        isCompleted = true;
    }

    bool isTaskCompleted() const {
        return isCompleted;
    }

    virtual void displayTask() const = 0; // Pure virtual function

    virtual ~TaskBase() {} // Virtual destructor to allow polymorphic behavior
};

class Task : public TaskBase {
public:
    Task(const std::string& desc, const std::string& date)
        : TaskBase(desc, date) {}

    void displayTask() const override {
        std::cout << "Description: " << description << ", Due Date: " << dueDate;
        if (isCompleted) {
            std::cout << " (Completed)" << std::endl;
        } else {
            std::cout << " (Not Completed)" << std::endl;
        }
    }
};

class RecurringTask : public TaskBase {
private:
    int frequency; // How often the task recurs (e.g., daily, weekly, monthly)

public:
    RecurringTask(const std::string& desc, int freq)
        : TaskBase(desc, ""), frequency(freq) {} // Recurring tasks don't have a due date

    void displayTask() const override {
        std::cout << "Recurring Task: Description: " << description;
        if (isCompleted) {
            std::cout << " (Completed)";
        } else {
            std::cout << " (Not Completed)";
        }

        std::cout << ", Frequency: ";
        if (frequency == 1) {
            std::cout << "Daily";
        } else if (frequency == 7) {
            std::cout << "Weekly";
        } else if (frequency == 30) {
            std::cout << "Monthly";
        } else {
            std::cout << "Unknown";
        }

        std::cout << std::endl;
    }
};

class ToDoList {
private:
    std::vector<TaskBase*> tasks; // Using pointers to TaskBase objects to allow polymorphism

public:
    ToDoList() {}

    void addTask(TaskBase* task) {
        tasks.push_back(task);
    }

    void displayTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks in the ToDo list." << std::endl;
        } else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << "[" << i + 1 << "] ";
                tasks[i]->displayTask(); // Polymorphic behavior using virtual function
            }
        }
    }

    void markTaskAsCompleted(int index) {
        if (isValidIndex(index)) {
            tasks[index]->markAsCompleted(); // Polymorphic behavior using virtual function
            std::cout << "Task marked as completed!" << std::endl;
        } else {
            std::cout << "Invalid task index!" << std::endl;
        }
    }

    void removeTask(int index) {
        if (isValidIndex(index)) {
            delete tasks[index]; // Free memory for the TaskBase object
            tasks.erase(tasks.begin() + index);
            std::cout << "Task removed!" << std::endl;
        } else {
            std::cout << "Invalid task index!" << std::endl;
        }
    }

    bool isValidIndex(int index) const {
        return index >= 0 && index < static_cast<int>(tasks.size());
    }

    ~ToDoList() {
        for (TaskBase* task : tasks) {
            delete task; // Free memory for all TaskBase objects
        }
    }
};

int main() {
    ToDoList todoList;
    int choice;

    do {
        std::cout << "===== ToDo List Application =====" << std::endl;
        std::cout << "1. Add Task\n2. Display Tasks\n3. Mark Task as Completed\n4. Remove Task\n0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int taskType;
                std::cout << "Select Task Type: 1. Regular Task 2. Recurring Task: ";
                std::cin >> taskType;

                std::string description;
                std::cout << "Enter task description: ";
                std::cin.ignore();
                std::getline(std::cin, description);

                if (taskType == 1) {
                    std::string dueDate;
                    std::cout << "Enter due date (yyyy-mm-dd): ";
                    std::cin >> dueDate;
                    Task* newTask = new Task(description, dueDate);
                    todoList.addTask(newTask);
                } else if (taskType == 2) {
                    int frequency;
                    std::cout << "Enter frequency (1: Daily, 7: Weekly, 30: Monthly): ";
                    std::cin >> frequency;
                    RecurringTask* newRecurringTask = new RecurringTask(description, frequency);
                    todoList.addTask(newRecurringTask);
                } else {
                    std::cout << "Invalid task type. Please try again." << std::endl;
                }

                std::cout << "Task added!" << std::endl;
                break;
            }
            case 2: {
                todoList.displayTasks();
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter the index of the task to mark as completed: ";
                std::cin >> index;
                todoList.markTaskAsCompleted(index - 1);
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter the index of the task to remove: ";
                std::cin >> index;
                todoList.removeTask(index - 1);
                break;
            }
            case 0:
                std::cout << "Exiting ToDo List Application. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;

    } while (choice != 0);

    return 0;
}
