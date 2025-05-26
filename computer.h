#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <iostream>

class Computer {
private:
    int id;
    std::string name;
    std::vector<int> componentIds;

public:
    Computer() = default;
    Computer(int id, std::string name);

    void addComponentId(int componentId);
    void removeComponentId(int componentId);
    void listComponents(const std::vector<class Component>& allComponents) const;

    int getId() const;
    const std::string& getName() const;
    const std::vector<int>& getComponentIds() const;

    friend std::ostream& operator<<(std::ostream& os, const Computer& c);
    friend std::istream& operator>>(std::istream& is, Computer& c);
};

#endif