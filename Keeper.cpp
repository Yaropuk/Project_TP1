#include "Keeper.h"
#include "Queue.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"
#include <stdexcept>
#include <iostream>

Keeper::Keeper() : capacity(10), size(0) {
    data = new Base*[capacity];
    std::cout << "Keeper default constructor called\n";
}

Keeper::Keeper(const Keeper& other) : capacity(other.capacity), size(other.size) {
    data = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i]->clone();
    }
    std::cout << "Keeper copy constructor called\n";
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    std::cout << "Keeper destructor called\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        
        capacity = other.capacity;
        size = other.size;
        data = new Base*[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i]->clone();
        }
    }
    std::cout << "Keeper assignment operator called\n";
    return *this;
}

void Keeper::resize() {
    capacity *= 2;
    Base** newData = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Keeper::add(Base* item) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = item;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Invalid index for removal");
    }
    
    delete data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty\n";
        return;
    }
    
    std::cout << "Keeper contains " << size << " objects:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i << ". " << data[i]->getType() << ": ";
        data[i]->print();
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Invalid index for editing");
    }
    data[index]->edit();
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        data[i]->saveToFile(file);
        file << "\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << "\n";
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    // Clear current data
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    size = 0;
    
    int count;
    file >> count;
    
    for (int i = 0; i < count; ++i) {
        std::string type;
        file >> type;
        
        Base* obj = nullptr;
        if (type == "Queue") {
            obj = new Queue();
        } else if (type == "List") {
            obj = new List();
        } else if (type == "Deque") {
            obj = new Deque();
        } else if (type == "Stack") {
            obj = new Stack();
        } else {
            throw std::runtime_error("Unknown object type in file");
        }
        
        obj->loadFromFile(file);
        add(obj);
    }
    file.close();
    std::cout << "Data loaded from " << filename << "\n";
}

int Keeper::getSize() const {
    return size;
}

Base* Keeper::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Invalid index");
    }
    return data[index];
}