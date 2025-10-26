#include "Queue.h"
#include <stdexcept>

Queue::Queue() : front(nullptr), rear(nullptr), size(0) {
    std::cout << "Queue default constructor called\n";
}

Queue::Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) {
    Node* temp = other.front;
    while (temp) {
        enqueue(temp->data);
        temp = temp->next;
    }
    std::cout << "Queue copy constructor called\n";
}

Queue::Queue(int initialSize, int values[]) : front(nullptr), rear(nullptr), size(0) {
    for (int i = 0; i < initialSize; ++i) {
        enqueue(values[i]);
    }
    std::cout << "Queue parameterized constructor called\n";
}

Queue::~Queue() {
    clear();
    std::cout << "Queue destructor called\n";
}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        Node* temp = other.front;
        while (temp) {
            enqueue(temp->data);
            temp = temp->next;
        }
    }
    std::cout << "Queue assignment operator called\n";
    return *this;
}

void Queue::enqueue(int value) {
    Node* newNode = new Node(value);
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    Node* temp = front;
    int value = front->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    size--;
    return value;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::getSize() const {
    return size;
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::print() const {
    if (isEmpty()) {
        std::cout << "Queue is empty\n";
        return;
    }
    Node* temp = front;
    std::cout << "Queue (" << size << " elements): ";
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

void Queue::edit() {
    if (isEmpty()) {
        std::cout << "Queue is empty, cannot edit\n";
        return;
    }
    
    std::cout << "Current queue: ";
    print();
    
    std::cout << "Choose action:\n";
    std::cout << "1. Enqueue element\n";
    std::cout << "2. Dequeue element\n";
    std::cout << "3. Change front element\n";
    
    int choice;
    std::cin >> choice;
    
    try {
        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter value to enqueue: ";
                std::cin >> value;
                enqueue(value);
                break;
            }
            case 2: {
                int value = dequeue();
                std::cout << "Dequeued: " << value << "\n";
                break;
            }
            case 3: {
                if (isEmpty()) throw std::runtime_error("Queue is empty");
                int value;
                std::cout << "Enter new value for front: ";
                std::cin >> value;
                front->data = value;
                break;
            }
            default:
                std::cout << "Invalid choice\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Queue::saveToFile(std::ofstream& file) const {
    file << "Queue " << size << " ";
    Node* temp = front;
    while (temp) {
        file << temp->data << " ";
        temp = temp->next;
    }
}

void Queue::loadFromFile(std::ifstream& file) {
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

Base* Queue::clone() const {
    return new Queue(*this);
}

const char* Queue::getType() const {
    return "Queue";
}

int Queue::getFront() const {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    return front->data;
}

int Queue::getRear() const {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    return rear->data;
}

void Queue::setFront(int value) {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    front->data = value;
}