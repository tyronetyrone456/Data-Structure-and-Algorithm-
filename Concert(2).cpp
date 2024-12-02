#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

class Person {
public:
    std::string name;
    int ticket_number;

    Person(const std::string &name, int ticket_number) : name(name), ticket_number(ticket_number) {}
};

class Queue {
private:
    std::queue<Person> queue;
    int ticket_counter;
    std::mutex queue_mutex;

public:
    Queue() : ticket_counter(1) {}

    void Enqueue(const std::string &name) {
        std::lock_guard<std::mutex> lock(queue_mutex);
        Person person(name, ticket_counter++);
        queue.push(person);
        std::cout << name << " added to the queue with Ticket #" << person.ticket_number << "\n";
        std::cout << "Queue size: " << queue.size() << "\n";
    }

    void AutoDequeue() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(1));

            std::lock_guard<std::mutex> lock(queue_mutex);
            if (!queue.empty()) {
                Person person = queue.front();
                std::cout << "\nAfter 1 minute...\n";
                std::cout << "Dequeue: " << person.name << " received a ticket (Ticket #" << person.ticket_number << ")\n";
                queue.pop();
                std::cout << "Queue size: " << queue.size() << "\n";
                if (!queue.empty()) {
                    Person next_person = queue.front();
                    std::cout << "Next in line: " << next_person.name << " (Ticket #" << next_person.ticket_number << ")\n";
                } else {
                    std::cout << "Queue is empty.\n";
                }
            }
        }
    }

    int Position(const std::string &name) {
        std::lock_guard<std::mutex> lock(queue_mutex);
        std::queue<Person> tempQueue = queue;
        int position = 1;

        while (!tempQueue.empty()) {
            Person person = tempQueue.front();
            if (person.name == name) {
                return position;
            }
            tempQueue.pop();
            position++;
        }

        return -1;
    }

    bool IsEmpty() const {
        return queue.empty();
    }
};

void DisplayMenu() {
    std::cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!\n";
    std::cout << "1. Enqueue a person\n";
    std::cout << "2. Check your position in the queue\n";
    std::cout << "3. Exit\n";
}

int main() {
    Queue ticketQueue;

    std::thread autoDequeueThread(&Queue::AutoDequeue, &ticketQueue);
    autoDequeueThread.detach();

    int choice;
    std::string name;

    while (true) {
        DisplayMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter the name: ";
            std::cin >> name;
            ticketQueue.Enqueue(name);
        } else if (choice == 2) {
            std::cout << "Enter your name or ticket number: ";
            std::cin >> name;
            int position = ticketQueue.Position(name);
            if (position != -1) {
                std::cout << name << " is currently at position " << position << " in the queue.\n";
            } else {
                std::cout << name << " is not in the queue.\n";
            }
        } else if (choice == 3) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}