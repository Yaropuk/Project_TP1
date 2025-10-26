#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <fstream>

class Keeper {
private:
    Base** data;
    int capacity;
    int size;

    void resize();

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();
    
    Keeper& operator=(const Keeper& other);
    
    void add(Base* item);
    void remove(int index);
    void printAll() const;
    void edit(int index);
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
    int getSize() const;
    Base* get(int index) const;
};

#endif