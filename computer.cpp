#include "computer.h"
#include "component.h"
#include <algorithm>
#include <sstream>


Computer::Computer(int id, std::string name) : id(id), name(std::move(name)) {}

void Computer::addComponentId(int componentId) {
    componentIds.push_back(componentId);
}

void Computer::removeComponentId(int componentId) {
    componentIds.erase(std::remove(componentIds.begin(), componentIds.end(), componentId), componentIds.end());
}

void Computer::listComponents(const std::vector<Component>& allComponents) const {
    for (int compId : componentIds) {
        auto it = std::find_if(allComponents.begin(), allComponents.end(),
            [compId](const Component& c) { return c.getId() == compId; });
        if (it != allComponents.end()) {
            it->display(false);
        }
    }
}

int Computer::getId() const { return id; }
const std::string& Computer::getName() const { return name; }
const std::vector<int>& Computer::getComponentIds() const { return componentIds; }

std::ostream& operator<<(std::ostream& os, const Computer& c) {
    os << c.id << " " << c.name << " " << c.componentIds.size() << "\n";
    for (int compId : c.componentIds)
        os << compId << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Computer& c) {
    std::string line;
    if (!std::getline(is, line)) return is;

    std::istringstream ss(line);

    ss >> c.id;

    std::string rest;
    std::getline(ss, rest);

    size_t pos = rest.find_last_of(' ');
    if (pos == std::string::npos) {
        c.name = rest;
        c.componentIds.clear();
        return is;
    }

    std::string countStr = rest.substr(pos + 1);
    c.name = rest.substr(0, pos);
    c.name.erase(0, c.name.find_first_not_of(' '));

    c.componentIds.clear();

    return is;
}
