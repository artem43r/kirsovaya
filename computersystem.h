#ifndef COMPUTERSYSTEM_H
#define COMPUTERSYSTEM_H

#include <vector>
#include <string>
#include "computer.h"
#include "component.h"

class ComputerSystem {
private:
    std::vector<Computer> computers;
    std::vector<Component> components;

public:
    void addComputer(const Computer& computer);
    void addComponent(const Component& component);
    void removeComputer(int computerId);
    void removeComponent(int componentId);

    std::vector<Computer>& getComputers();
    std::vector<Component>& getComponents();

    void addComponentToComputer(int computerId, int componentId);
    void extractComponentFromComputer(int computerId, int componentId);
    void moveComponentBetweenComputers(int fromComputerId, int toComputerId, int componentId);

    void listComputers() const;
    void findComponentByType(ComponentType type) const;
    void findComponentByManufacturer(const std::string& manufacturer) const;
    void findComponentByStatus(ComponentStatus status) const;
    void findComponentById(int id) const;
    void findComponentsByComputerId(int computerId) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
