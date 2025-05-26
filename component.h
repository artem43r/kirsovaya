#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "componenttype.h"
#include "componentstatus.h"
#include <iostream>

class Component {
private:
    int id;
    std::string name;
    std::string manufacturer;
    ComponentStatus status;
    ComponentType type;

public:
    Component() = default;
    Component(int id, std::string name, std::string manufacturer, ComponentType type);

    void display(bool showStatus = true) const;
    int getId() const;
    const std::string& getName() const;
    const std::string& getManufacturer() const;
    ComponentStatus getStatus() const;
    ComponentType getType() const;
    void setStatus(ComponentStatus newStatus);

    friend std::ostream& operator<<(std::ostream& os, const Component& c);
    friend std::istream& operator>>(std::istream& is, Component& c);
};

#endif