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

