#ifndef LIST_H
#define LIST_H

#include "Queue.h"

class List : public Queue {
public:
    List();
    List(const List& other);
    List(int initialSize, int values[]);
    ~List();
    
    List& operator=(const List& other);
    
    // Специфичные для List методы
    void insertAt(int position, int value);
    void removeAt(int position);
    int getAt(int position) const;
    void setAt(int position, int value);
    
    // Переопределенные виртуальные методы
    void print() const override;
    void edit() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
    Base* clone() const override;
    const char* getType() const override;
};

#endif