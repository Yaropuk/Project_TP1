#include "Stack.h"
#include <stdexcept>

Stack::Stack() : Queue() {
    std::cout << "Stack default constructor called\n";
}

Stack::Stack(const Stack& other) : Queue(other) {
    std::cout << "Stack copy constructor called\n";
}

Stack::Stack(int initialSize, int values[]) : Queue(initialSize, values) {
    std::cout << "Stack parameterized constructor called\n";
}

Stack::~Stack() {
    std::cout << "Stack destructor called\n";
}

Stack& Stack::operator=(const Stack& other) {
    Queue::operator=(other);
    std::cout << "Stack assignment operator called\n";
    return *this;
}

void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = front;
    front = newNode;
    if (!rear) rear = newNode;
    size++;
}

int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty stack");
    }
    
    Node* temp = front;
    int value = front->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    size--;
    return value;
}

int Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Cannot peek empty stack");
    }
    return front->data;
}

void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Stack is empty\n";
        return;
    }
    Node* temp = front;
    std::cout << "Stack (" << size << " elements, top first): ";
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

void Stack::edit() {
    if (isEmpty()) {
        std::cout << "Stack is empty, cannot edit\n";
        return;
    }
    
    std::cout << "Current stack: ";
    print();
    
    std::cout << "Choose action:\n";
    std::cout << "1. Push element\n";
    std::cout << "2. Pop element\n";
    std::cout << "3. Peek top element\n";
    
    int choice;
    std::cin >> choice;
    
    try {
        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter value to push: ";
                std::cin >> value;
                push(value);
                break;
            }
            case 2: {
                int value = pop();
                std::cout << "Popped: " << value << "\n";
                break;
            }
            case 3: {
                std::cout << "Top element: " << peek() << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Stack::saveToFile(std::ofstream& file) const {
    file << "Stack " << size << " ";
    Node* temp = front;
    while (temp) {
        file << temp->data << " ";
        temp = temp->next;
    }
}

void Stack::loadFromFile(std::ifstream& file) {
    clear();
    std::string type;
    int count;
    file >> type >> count;
    
    for (int i = 0; i < count; ++i) {
        int value;
        file >> value;
        push(value);
    }
}

Base* Stack::clone() const {
    return new Stack(*this);
}

const char* Stack::getType() const {
    return "Stack";
}