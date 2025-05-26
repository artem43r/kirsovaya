#include "component.h"
#include <iostream>

static std::string componentTypeToString(ComponentType type) {
    switch (type) {
    case ComponentType::Processor: return "Processor";
    case ComponentType::Memory: return "Memory";
    case ComponentType::Storage: return "Storage";
    case ComponentType::GraphicsCard: return "GraphicsCard";
    case ComponentType::Motherboard: return "Motherboard";
    case ComponentType::Other: return "Other";
    default: return "Unknown";
    }
}

static ComponentType stringToComponentType(const std::string& str) {
    if (str == "Processor") return ComponentType::Processor;
    if (str == "Memory") return ComponentType::Memory;
    if (str == "Storage") return ComponentType::Storage;
    if (str == "GraphicsCard") return ComponentType::GraphicsCard;
    if (str == "Motherboard") return ComponentType::Motherboard;
    if (str == "Other") return ComponentType::Other;
    return ComponentType::Other;
}

static std::string componentStatusToString(ComponentStatus status) {
    switch (status) {
    case ComponentStatus::Available: return "Available";
    case ComponentStatus::InUse: return "InUse";
    default: return "Unknown";
    }
}

static ComponentStatus stringToComponentStatus(const std::string& str) {
    if (str == "Available") return ComponentStatus::Available;
    if (str == "InUse") return ComponentStatus::InUse;
    return ComponentStatus::Available;
}

Component::Component(int id, std::string name, std::string manufacturer, ComponentType type)
    : id(id), name(std::move(name)), manufacturer(std::move(manufacturer)), status(ComponentStatus::Available), type(type) {}

void Component::display(bool showStatus) const {
    std::cout << "ID: " << id
        << ", Name: " << name
        << ", Manufacturer: " << manufacturer
        << ", Type: " << componentTypeToString(type);
    if (showStatus) {
        std::cout << ", Status: " << componentStatusToString(status);
    }
    std::cout << std::endl;
}

int Component::getId() const { return id; }
const std::string& Component::getName() const { return name; }
const std::string& Component::getManufacturer() const { return manufacturer; }
ComponentStatus Component::getStatus() const { return status; }
ComponentType Component::getType() const { return type; }
void Component::setStatus(ComponentStatus newStatus) { status = newStatus; }

std::ostream& operator<<(std::ostream& os, const Component& c) {
    os << c.id << " " << c.name << " " << c.manufacturer << " "
        << componentTypeToString(c.type) << " "
        << componentStatusToString(c.status) << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Component& c) {
    std::string typeStr, statusStr;
    is >> c.id >> c.name >> c.manufacturer >> typeStr >> statusStr;
    c.type = stringToComponentType(typeStr);
    c.status = stringToComponentStatus(statusStr);
    return is;
}