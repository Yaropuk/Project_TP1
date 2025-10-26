#include "Deque.h"
#include <stdexcept>

Deque::Deque() : Queue() {
    std::cout << "Deque default constructor called\n";
}

Deque::Deque(const Deque& other) : Queue(other) {
    std::cout << "Deque copy constructor called\n";
}

Deque::Deque(int initialSize, int values[]) : Queue(initialSize, values) {
    std::cout << "Deque parameterized constructor called\n";
}

Deque::~Deque() {
    std::cout << "Deque destructor called\n";
}

Deque& Deque::operator=(const Deque& other) {
    Queue::operator=(other);
    std::cout << "Deque assignment operator called\n";
    return *this;
}

void Deque::pushFront(int value) {
    Node* newNode = new Node(value);
    newNode->next = front;
    front = newNode;
    if (!rear) rear = newNode;
    size++;
}

void Deque::pushRear(int value) {
    enqueue(value);
}

int Deque::popFront() {
    return dequeue();
}

int Deque::popRear() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }
    
    if (front == rear) {
        int value = front->data;
        delete front;
        front = rear = nullptr;
        size--;
        return value;
    }
    
    Node* current = front;
    while (current->next != rear) {
        current = current->next;
    }
    
    int value = rear->data;
    delete rear;
    rear = current;
    rear->next = nullptr;
    size--;
    return value;
}

void Deque::print() const {
    if (isEmpty()) {
        std::cout << "Deque is empty\n";
        return;
    }
    Node* temp = front;
    std::cout << "Deque (" << size << " elements): ";
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

void Deque::edit() {
    if (isEmpty()) {
        std::cout << "Deque is empty, cannot edit\n";
        return;
    }
    
    std::cout << "Current deque: ";
    print();
    
    std::cout << "Choose action:\n";
    std::cout << "1. Push to front\n";
    std::cout << "2. Push to rear\n";
    std::cout << "3. Pop from front\n";
    std::cout << "4. Pop from rear\n";
    
    int choice;
    std::cin >> choice;
    
    try {
        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter value to push front: ";
                std::cin >> value;
                pushFront(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter value to push rear: ";
                std::cin >> value;
                pushRear(value);
                break;
            }
            case 3: {
                int value = popFront();
                std::cout << "Popped from front: " << value << "\n";
                break;
            }
            case 4: {
                int value = popRear();
                std::cout << "Popped from rear: " << value << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Deque::saveToFile(std::ofstream& file) const {
    file << "Deque " << size << " ";
    Node* temp = front;
    while (temp) {
        file << temp->data << " ";
        temp = temp->next;
    }
}

void Deque::loadFromFile(std::ifstream& file) {
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

Base* Deque::clone() const {
    return new Deque(*this);
}

const char* Deque::getType() const {
    return "Deque";
}