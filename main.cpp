#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "component.h"
#include "computer.h"
#include "computersystem.h"
#include "componenttype.h"
#include "componentstatus.h"

using namespace std;

int getChoice() {
    int choice;
    cin >> choice;
    return choice;
}

void addComputer(ComputerSystem& system) {
    int id;
    string name;

    cout << "Введите ID компьютера: ";
    cin >> id;
    cout << "Введите название компьютера: ";
    cin.ignore();
    getline(cin, name);

    Computer comp(id, name);
    system.addComputer(comp);

    cout << "Компьютер добавлен успешно!\n";
}

void addComponent(ComputerSystem& system) {
    int id;
    string name, manufacturer;
    int typeInt;

    cout << "Введите ID компонента: ";
    cin >> id;
    cout << "Введите название компонента: ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите производителя компонента: ";
    getline(cin, manufacturer);
    cout << "Введите тип компонента (0 - Processor, 1 - Memory, 2 - Storage, 3 - GraphicsCard, 4 - Motherboard): ";
    cin >> typeInt;

    ComponentType type = static_cast<ComponentType>(typeInt);

    Component comp(id, name, manufacturer, type);
    system.addComponent(comp);

    cout << "Компонент добавлен успешно!\n";
}

void removeComponent(ComputerSystem& system) {
    int id;
    cout << "Введите ID компонента для удаления: ";
    cin >> id;

    system.removeComponent(id);
    cout << "Компонент удален успешно!\n";
}

void moveComponent(ComputerSystem& system) {
    int componentId, fromId, toId;
    cout << "Введите ID компонента для перемещения: ";
    cin >> componentId;
    cout << "Введите ID компьютера-отправителя: ";
    cin >> fromId;
    cout << "Введите ID компьютера-получателя: ";
    cin >> toId;

    system.moveComponentBetweenComputers(fromId, toId, componentId);
    cout << "Компонент перемещен успешно!\n";
}

void addComponentToComputer(ComputerSystem& system) {
    int computerId, componentId;
    cout << "Введите ID компьютера: ";
    cin >> computerId;
    cout << "Введите ID компонента для добавления: ";
    cin >> componentId;

    system.addComponentToComputer(computerId, componentId);
    cout << "Компонент добавлен к компьютеру успешно!\n";
}

void extractComponentFromComputer(ComputerSystem& system) {
    int computerId, componentId;
    cout << "Введите ID компьютера: ";
    cin >> computerId;
    cout << "Введите ID компонента для изъятия: ";
    cin >> componentId;

    system.extractComponentFromComputer(computerId, componentId);
    cout << "Компонент изъят из компьютера успешно!\n";
}

void searchByType(ComputerSystem& system) {
    int typeInt;
    cout << "Введите тип компонента для поиска (0 - Processor, 1 - Memory, 2 - Storage, 3 - GraphicsCard, 4 - Motherboard): ";
    cin >> typeInt;
    system.findComponentByType(static_cast<ComponentType>(typeInt));
}

void searchByManufacturer(ComputerSystem& system) {
    cout << "Введите производителя для поиска: ";
    cin.ignore();
    string manufacturer;
    getline(cin, manufacturer);
    system.findComponentByManufacturer(manufacturer);
}

void searchByStatus(ComputerSystem& system) {
    int statusInt;
    cout << "Введите статус компонента для поиска (0 - Available, 1 - InUse): ";
    cin >> statusInt;
    system.findComponentByStatus(static_cast<ComponentStatus>(statusInt));
}

void searchById(ComputerSystem& system) {
    int id;
    cout << "Введите инвентарный номер компонента для поиска: ";
    cin >> id;
    system.findComponentById(id);
}

void searchComponentsByComputerId(ComputerSystem& system) {
    int computerId;
    cout << "Введите ID компьютера для поиска его компонентов: ";
    cin >> computerId;
    system.findComponentsByComputerId(computerId);
}

void listComputers(ComputerSystem& system) {
    system.listComputers();
}

void saveToFile(ComputerSystem& system) {
    std::string filename;
    std::cout << "Введите имя файла для сохранения: ";
    std::cin >> filename;

    system.saveToFile(filename);
    std::cout << "Данные успешно сохранены в файл " << filename << std::endl;
}

void loadFromFile(ComputerSystem& system) {
    std::string filename;
    std::cout << "Введите имя файла для загрузки: ";
    std::cin >> filename;

    system.loadFromFile(filename);
    std::cout << "Данные успешно загружены из файла " << filename << std::endl;
}

void displayMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Добавить компьютер\n";
    std::cout << "2. Добавить компонент\n";
    std::cout << "3. Удалить компонент\n";
    std::cout << "4. Переместить компонент между компьютерами\n";
    std::cout << "5. Добавить компонент в компьютер\n";
    std::cout << "6. Изъять компонент из компьютера\n";
    std::cout << "7. Поиск по типу компонента\n";
    std::cout << "8. Поиск по производителю\n";
    std::cout << "9. Поиск по статусу компонента\n";
    std::cout << "10. Поиск по инвентарному номеру компонента\n";
    std::cout << "11. Поиск компонентов, принадлежащих компьютеру\n";
    std::cout << "12. Список всех компьютеров и их компонентов\n";
    std::cout << "13. Сохранить систему в файл\n";
    std::cout << "14. Загрузить систему из файла\n";
    std::cout << "15. Выйти\n";
    std::cout << "Выберите действие: ";
}

int main() {
    system("color F0");
    setlocale(LC_ALL, "Russian");
    ComputerSystem system;

    while (true) {
        displayMenu();
        int choice = getChoice();

        switch (choice) {
        case 1: addComputer(system); break;
        case 2: addComponent(system); break;
        case 3: removeComponent(system); break;
        case 4: moveComponent(system); break;
        case 5: addComponentToComputer(system); break;
        case 6: extractComponentFromComputer(system); break;
        case 7: searchByType(system); break;
        case 8: searchByManufacturer(system); break;
        case 9: searchByStatus(system); break;
        case 10: searchById(system); break;
        case 11: searchComponentsByComputerId(system); break;
        case 12: listComputers(system); break;
        case 13: saveToFile(system); break;
        case 14: loadFromFile(system); break;
        case 15:
            std::cout << "Выход из программы.\n";
            return 0;
        default:
            std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }

    return 0;
}