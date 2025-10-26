#ifndef DEQUE_H
#define DEQUE_H

#include "Queue.h"

class Deque : public Queue {
public:
    Deque();
    Deque(const Deque& other);
    Deque(int initialSize, int values[]);
    ~Deque();
    
    Deque& operator=(const Deque& other);
    
    // Специфичные для Deque методы
    void pushFront(int value);
    void pushRear(int value);
    int popFront();
    int popRear();
    
    // Переопределенные виртуальные методы
    void print() const override;
    void edit() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
    Base* clone() const override;
    const char* getType() const override;
};

#endif 