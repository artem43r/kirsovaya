#include "computersystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

void ComputerSystem::addComputer(const Computer& computer) {
    computers.push_back(computer);
}

void ComputerSystem::addComponent(const Component& component) {
    components.push_back(component);
}

void ComputerSystem::removeComputer(int computerId) {
    computers.erase(std::remove_if(computers.begin(), computers.end(),
        [computerId](const Computer& c) { return c.getId() == computerId; }),
        computers.end());
}

void ComputerSystem::removeComponent(int componentId) {
    components.erase(std::remove_if(components.begin(), components.end(),
        [componentId](const Component& c) { return c.getId() == componentId; }),
        components.end());

    for (auto& comp : computers) {
        comp.removeComponentId(componentId);
    }
}

std::vector<Computer>& ComputerSystem::getComputers() {
    return computers;
}

std::vector<Component>& ComputerSystem::getComponents() {
    return components;
}

void ComputerSystem::addComponentToComputer(int computerId, int componentId) {
    auto compIt = std::find_if(computers.begin(), computers.end(),
        [computerId](const Computer& c) { return c.getId() == computerId; });
    auto compoIt = std::find_if(components.begin(), components.end(),
        [componentId](Component& c) { return c.getId() == componentId; });

    if (compIt == computers.end()) {
        std::cout << "Компьютер с ID " << computerId << " не найден.\n";
        return;
    }
    if (compoIt == components.end()) {
        std::cout << "Компонент с ID " << componentId << " не найден.\n";
        return;
    }
    if (compoIt->getStatus() == ComponentStatus::InUse) {
        std::cout << "Компонент уже используется в другом компьютере.\n";
        return;
    }
    if (std::find(compIt->getComponentIds().begin(), compIt->getComponentIds().end(), componentId) != compIt->getComponentIds().end()) {
        std::cout << "Компонент уже добавлен к этому компьютеру.\n";
        return;
    }

    compIt->addComponentId(componentId);
    compoIt->setStatus(ComponentStatus::InUse);
    std::cout << "Компонент добавлен к компьютеру успешно!\n";
}

void ComputerSystem::extractComponentFromComputer(int computerId, int componentId) {
    auto compIt = std::find_if(computers.begin(), computers.end(),
        [computerId](const Computer& c) { return c.getId() == computerId; });
    auto compoIt = std::find_if(components.begin(), components.end(),
        [componentId](const Component& c) { return c.getId() == componentId; });

    if (compIt != computers.end() && compoIt != components.end()) {
        compIt->removeComponentId(componentId);
        compoIt->setStatus(ComponentStatus::Available);
    }
}

void ComputerSystem::moveComponentBetweenComputers(int fromComputerId, int toComputerId, int componentId) {
    extractComponentFromComputer(fromComputerId, componentId);
    addComponentToComputer(toComputerId, componentId);
}

void ComputerSystem::listComputers() const {
    for (const auto& comp : computers) {
        std::cout << "Computer ID: " << comp.getId() << ", Name: " << comp.getName() << std::endl;
        comp.listComponents(components);
    }
}

void ComputerSystem::findComponentByType(ComponentType type) const {
    for (const auto& c : components) {
        if (c.getType() == type) c.display();
    }
}

void ComputerSystem::findComponentByManufacturer(const std::string& manufacturer) const {
    for (const auto& c : components) {
        if (c.getManufacturer() == manufacturer) c.display();
    }
}

void ComputerSystem::findComponentByStatus(ComponentStatus status) const {
    for (const auto& c : components) {
        if (c.getStatus() == status) c.display();
    }
}

void ComputerSystem::findComponentById(int id) const {
    for (const auto& c : components) {
        if (c.getId() == id) c.display();
    }
}

void ComputerSystem::findComponentsByComputerId(int computerId) const {
    auto compIt = std::find_if(computers.begin(), computers.end(),
        [computerId](const Computer& c) { return c.getId() == computerId; });
    if (compIt != computers.end()) {
        std::cout << "Components for computer ID " << computerId << ":\n";
        compIt->listComponents(components);
    }
    else {
        std::cout << "Computer with ID " << computerId << " not found.\n";
    }
}

void ComputerSystem::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    file << computers.size() << "\n";
    for (const auto& comp : computers) {
        file << comp;
    }

    file << "COMPONENTS\n";
    file << components.size() << "\n";
    for (const auto& comp : components) {
        file << comp;
    }

    file.close();
}

void ComputerSystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    computers.clear();
    components.clear();

    std::string line;

    // Читаем количество компьютеров
    if (!std::getline(file, line)) {
        std::cerr << "Ошибка чтения количества компьютеров\n";
        return;
    }
    size_t nComputers = 0;
    try {
        nComputers = std::stoul(line);
    }
    catch (...) {
        std::cerr << "Ошибка: неверный формат количества компьютеров\n";
        return;
    }

    for (size_t i = 0; i < nComputers; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Ошибка чтения данных компьютера\n";
            return;
        }
        std::istringstream iss(line);
        Computer c;
        iss >> c;

        size_t pos = line.find_last_of(' ');
        if (pos == std::string::npos) {
            std::cerr << "Ошибка формата компьютера\n";
            return;
        }
        std::string countStr = line.substr(pos + 1);
        size_t count = 0;
        try {
            count = std::stoul(countStr);
        }
        catch (...) {
            count = 0;
        }

        for (size_t j = 0; j < count; ++j) {
            if (!std::getline(file, line)) {
                std::cerr << "Ошибка чтения ID компонента компьютера\n";
                return;
            }
            int compId = 0;
            try {
                compId = std::stoi(line);
            }
            catch (...) {
                std::cerr << "Ошибка формата ID компонента\n";
                return;
            }
            c.addComponentId(compId);
        }

        computers.push_back(c);
    }

    do {
        if (!std::getline(file, line)) {
            std::cerr << "Ошибка чтения маркера COMPONENTS\n";
            return;
        }
    } while (line.empty());

    if (line != "COMPONENTS") {
        std::cerr << "Ошибка: ожидался маркер COMPONENTS, получено: " << line << std::endl;
        return;
    }

    if (!std::getline(file, line)) {
        std::cerr << "Ошибка чтения количества компонентов\n";
        return;
    }
    size_t nComponents = 0;
    try {
        nComponents = std::stoul(line);
    }
    catch (...) {
        std::cerr << "Ошибка: неверный формат количества компонентов\n";
        return;
    }

    for (size_t i = 0; i < nComponents; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Ошибка чтения данных компонента\n";
            return;
        }
        std::istringstream iss(line);
        Component c;
        iss >> c;
        components.push_back(c);
    }
}
