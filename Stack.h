#ifndef STACK_H
#define STACK_H

#include "Queue.h"

class Stack : public Queue {
public:
    Stack();
    Stack(const Stack& other);
    Stack(int initialSize, int values[]);
    ~Stack();
    
    Stack& operator=(const Stack& other);
    
    // Специфичные для Stack методы
    void push(int value);
    int pop();
    int peek() const;
    
    // Переопределенные виртуальные методы
    void print() const override;
    void edit() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
    Base* clone() const override;
    const char* getType() const override;
};

#endif