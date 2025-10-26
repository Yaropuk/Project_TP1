#include <iostream>
#include <cstdlib>
#include "Keeper.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"

void showMainMenu() {
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. Add new container\n";
    std::cout << "2. Remove container\n";
    std::cout << "3. Print all containers\n";
    std::cout << "4. Edit container\n";
    std::cout << "5. Save to file\n";
    std::cout << "6. Load from file\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose option: ";
}

void showAddMenu() {
    std::cout << "\n=== Add Container ===\n";
    std::cout << "1. Add List\n";
    std::cout << "2. Add Deque\n";
    std::cout << "3. Add Stack\n";
    std::cout << "4. Back to main menu\n";
    std::cout << "Choose option: ";
}

Base* createContainer(int choice) {
    std::cout << "Choose initialization:\n";
    std::cout << "1. Empty container\n";
    std::cout << "2. Container with initial values\n";
    
    int initChoice;
    std::cin >> initChoice;
    
    if (initChoice == 1) {
        switch (choice) {
            case 1: return new List();
            case 2: return new Deque();
            case 3: return new Stack();
            default: return nullptr;
        }
    } else {
        std::cout << "Enter number of initial elements: ";
        int count;
        std::cin >> count;
        
        if (count <= 0) {
            throw std::runtime_error("Invalid number of elements");
        }
        
        int* values = new int[count];
        std::cout << "Enter " << count << " values: ";
        for (int i = 0; i < count; ++i) {
            std::cin >> values[i];
        }
        
        Base* result = nullptr;
        switch (choice) {
            case 1: result = new List(count, values); break;
            case 2: result = new Deque(count, values); break;
            case 3: result = new Stack(count, values); break;
        }
        
        delete[] values;
        return result;
    }
}

int main() {
    Keeper keeper;
    int choice;
    
    std::cout << "=== Container Management System ===\n";
    
    do {
        showMainMenu();
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    int addChoice;
                    do {
                        showAddMenu();
                        std::cin >> addChoice;
                        
                        if (addChoice >= 1 && addChoice <= 3) {
                            Base* newContainer = createContainer(addChoice);
                            if (newContainer) {
                                keeper.add(newContainer);
                                std::cout << "Container added successfully\n";
                            }
                        } else if (addChoice != 4) {
                            std::cout << "Invalid choice\n";
                        }
                    } while (addChoice != 4);
                    break;
                }
                
                case 2: {
                    if (keeper.getSize() == 0) {
                        std::cout << "No containers to remove\n";
                        break;
                    }
                    keeper.printAll();
                    std::cout << "Enter index to remove: ";
                    int index;
                    std::cin >> index;
                    keeper.remove(index);
                    std::cout << "Container removed successfully\n";
                    break;
                }
                
                case 3:
                    keeper.printAll();
                    break;
                
                case 4: {
                    if (keeper.getSize() == 0) {
                        std::cout << "No containers to edit\n";
                        break;
                    }
                    keeper.printAll();
                    std::cout << "Enter index to edit: ";
                    int index;
                    std::cin >> index;
                    keeper.edit(index);
                    break;
                }
                
                case 5: {
                    std::cout << "Enter filename: ";
                    std::string filename;
                    std::cin >> filename;
                    keeper.saveToFile(filename.c_str());
                    break;
                }
                
                case 6: {
                    std::cout << "Enter filename: ";
                    std::string filename;
                    std::cin >> filename;
                    keeper.loadFromFile(filename.c_str());
                    break;
                }
                
                case 7:
                    std::cout << "Exiting...\n";
                    break;
                
                default:
                    std::cout << "Invalid choice\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
                    }
                } while (choice != 7);
                
                return 0;
            }