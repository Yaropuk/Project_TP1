#ifndef QUEUE_H
#define QUEUE_H

#include "Base.h"
#include <fstream>

class Queue : public Base {
protected:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    int size;

public:
    // Конструкторы и деструктор
    Queue();
    Queue(const Queue& other);
    Queue(int initialSize, int values[]);
    virtual ~Queue();
    
    // Операторы
    Queue& operator=(const Queue& other);
    
    // Базовые методы
    virtual void enqueue(int value);
    virtual int dequeue();
    bool isEmpty() const;
    int getSize() const;
    void clear();
    
    // Виртуальные методы от Base
    void print() const override;
    void edit() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
    Base* clone() const override;
    const char* getType() const override;
    
    // Get/Set методы
    virtual int getFront() const;
    virtual int getRear() const;
    virtual void setFront(int value);
};

#endif