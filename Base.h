#ifndef BASE_H
#define BASE_H

#include <iostream>

class Base {
public:
    virtual ~Base() = default;
    virtual void print() const = 0;
    virtual void edit() = 0;
    virtual void saveToFile(std::ofstream& file) const = 0;
    virtual void loadFromFile(std::ifstream& file) = 0;
    virtual Base* clone() const = 0;
    virtual const char* getType() const = 0;
};

#endif