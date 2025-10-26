#include "List.h"
#include <stdexcept>

List::List() : Queue() {
    std::cout << "List default constructor called\n";
}

List::List(const List& other) : Queue(other) {
    std::cout << "List copy constructor called\n";
}

List::List(int initialSize, int values[]) : Queue(initialSize, values) {
    std::cout << "List parameterized constructor called\n";
}

List::~List() {
    std::cout << "List destructor called\n";
}

List& List::operator=(const List& other) {
    Queue::operator=(other);
    std::cout << "List assignment operator called\n";
    return *this;
}

void List::insertAt(int position, int value) {
    if (position < 0 || position > size) {
        throw std::runtime_error("Invalid position for insertion");
    }
    
    if (position == 0) {
        Node* newNode = new Node(value);
        newNode->next = front;
        front = newNode;
        if (!rear) rear = newNode;
    } else if (position == size) {
        enqueue(value);
    } else {
        Node* current = front;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }
    size++;
}

void List::removeAt(int position) {
    if (position < 0 || position >= size) {
        throw std::runtime_error("Invalid position for removal");
    }
    
    if (position == 0) {
        dequeue();
    } else {
        Node* current = front;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        Node* toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete == rear) rear = current;
        delete toDelete;
        size--;
    }
}

int List::getAt(int position) const {
    if (position < 0 || position >= size) {
        throw std::runtime_error("Invalid position");
    }
    
    Node* current = front;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->data;
}

void List::setAt(int position, int value) {
    if (position < 0 || position >= size) {
        throw std::runtime_error("Invalid position");
    }
    
    Node* current = front;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    current->data = value;
}

void List::print() const {
    if (isEmpty()) {
        std::cout << "List is empty\n";
        return;
    }
    Node* temp = front;
    std::cout << "List (" << size << " elements): ";
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

void List::edit() {
    if (isEmpty()) {
        std::cout << "List is empty, cannot edit\n";
        return;
    }
    
    std::cout << "Current list: ";
    print();
    
    std::cout << "Choose action:\n";
    std::cout << "1. Insert element at position\n";
    std::cout << "2. Remove element at position\n";
    std::cout << "3. Change element at position\n";
    std::cout << "4. Get element at position\n";
    
    int choice;
    std::cin >> choice;
    
    try {
        switch (choice) {
            case 1: {
                int pos, value;
                std::cout << "Enter position and value: ";
                std::cin >> pos >> value;
                insertAt(pos, value);
                break;
            }
            case 2: {
                int pos;
                std::cout << "Enter position to remove: ";
                std::cin >> pos;
                removeAt(pos);
                break;
            }
            case 3: {
                int pos, value;
                std::cout << "Enter position and new value: ";
                std::cin >> pos >> value;
                setAt(pos, value);
                break;
            }
            case 4: {
                int pos;
                std::cout << "Enter position: ";
                std::cin >> pos;
                std::cout << "Value at position " << pos << ": " << getAt(pos) << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void List::saveToFile(std::ofstream& file) const {
    file << "List " << size << " ";
    Node* temp = front;
    while (temp) {
        file << temp->data << " ";
        temp = temp->next;
    }
}

void List::loadFromFile(std::ifstream& file) {
    clear();
    std::string type;
    int count;
    file >> type >> count;
    
    for (int i = 0; i < count; ++i) {
        int value;
        file >> value;
        enqueue(value);
    }
}

Base* List::clone() const {
    return new List(*this);
}

const char* List::getType() const {
    return "List";
}