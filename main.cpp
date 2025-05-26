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

    cout << "������� ID ����������: ";
    cin >> id;
    cout << "������� �������� ����������: ";
    cin.ignore();
    getline(cin, name);

    Computer comp(id, name);
    system.addComputer(comp);

    cout << "��������� �������� �������!\n";
}

void addComponent(ComputerSystem& system) {
    int id;
    string name, manufacturer;
    int typeInt;

    cout << "������� ID ����������: ";
    cin >> id;
    cout << "������� �������� ����������: ";
    cin.ignore();
    getline(cin, name);
    cout << "������� ������������� ����������: ";
    getline(cin, manufacturer);
    cout << "������� ��� ���������� (0 - Processor, 1 - Memory, 2 - Storage, 3 - GraphicsCard, 4 - Motherboard): ";
    cin >> typeInt;

    ComponentType type = static_cast<ComponentType>(typeInt);

    Component comp(id, name, manufacturer, type);
    system.addComponent(comp);

    cout << "��������� �������� �������!\n";
}

void removeComponent(ComputerSystem& system) {
    int id;
    cout << "������� ID ���������� ��� ��������: ";
    cin >> id;

    system.removeComponent(id);
    cout << "��������� ������ �������!\n";
}

void moveComponent(ComputerSystem& system) {
    int componentId, fromId, toId;
    cout << "������� ID ���������� ��� �����������: ";
    cin >> componentId;
    cout << "������� ID ����������-�����������: ";
    cin >> fromId;
    cout << "������� ID ����������-����������: ";
    cin >> toId;

    system.moveComponentBetweenComputers(fromId, toId, componentId);
    cout << "��������� ��������� �������!\n";
}

void addComponentToComputer(ComputerSystem& system) {
    int computerId, componentId;
    cout << "������� ID ����������: ";
    cin >> computerId;
    cout << "������� ID ���������� ��� ����������: ";
    cin >> componentId;

    system.addComponentToComputer(computerId, componentId);
    cout << "��������� �������� � ���������� �������!\n";
}

void extractComponentFromComputer(ComputerSystem& system) {
    int computerId, componentId;
    cout << "������� ID ����������: ";
    cin >> computerId;
    cout << "������� ID ���������� ��� �������: ";
    cin >> componentId;

    system.extractComponentFromComputer(computerId, componentId);
    cout << "��������� ����� �� ���������� �������!\n";
}

void searchByType(ComputerSystem& system) {
    int typeInt;
    cout << "������� ��� ���������� ��� ������ (0 - Processor, 1 - Memory, 2 - Storage, 3 - GraphicsCard, 4 - Motherboard): ";
    cin >> typeInt;
    system.findComponentByType(static_cast<ComponentType>(typeInt));
}

void searchByManufacturer(ComputerSystem& system) {
    cout << "������� ������������� ��� ������: ";
    cin.ignore();
    string manufacturer;
    getline(cin, manufacturer);
    system.findComponentByManufacturer(manufacturer);
}

void searchByStatus(ComputerSystem& system) {
    int statusInt;
    cout << "������� ������ ���������� ��� ������ (0 - Available, 1 - InUse): ";
    cin >> statusInt;
    system.findComponentByStatus(static_cast<ComponentStatus>(statusInt));
}

void searchById(ComputerSystem& system) {
    int id;
    cout << "������� ����������� ����� ���������� ��� ������: ";
    cin >> id;
    system.findComponentById(id);
}

void searchComponentsByComputerId(ComputerSystem& system) {
    int computerId;
    cout << "������� ID ���������� ��� ������ ��� �����������: ";
    cin >> computerId;
    system.findComponentsByComputerId(computerId);
}

void listComputers(ComputerSystem& system) {
    system.listComputers();
}

void saveToFile(ComputerSystem& system) {
    std::string filename;
    std::cout << "������� ��� ����� ��� ����������: ";
    std::cin >> filename;

    system.saveToFile(filename);
    std::cout << "������ ������� ��������� � ���� " << filename << std::endl;
}

void loadFromFile(ComputerSystem& system) {
    std::string filename;
    std::cout << "������� ��� ����� ��� ��������: ";
    std::cin >> filename;

    system.loadFromFile(filename);
    std::cout << "������ ������� ��������� �� ����� " << filename << std::endl;
}

void displayMenu() {
    std::cout << "\n����:\n";
    std::cout << "1. �������� ���������\n";
    std::cout << "2. �������� ���������\n";
    std::cout << "3. ������� ���������\n";
    std::cout << "4. ����������� ��������� ����� ������������\n";
    std::cout << "5. �������� ��������� � ���������\n";
    std::cout << "6. ������ ��������� �� ����������\n";
    std::cout << "7. ����� �� ���� ����������\n";
    std::cout << "8. ����� �� �������������\n";
    std::cout << "9. ����� �� ������� ����������\n";
    std::cout << "10. ����� �� ������������ ������ ����������\n";
    std::cout << "11. ����� �����������, ������������� ����������\n";
    std::cout << "12. ������ ���� ����������� � �� �����������\n";
    std::cout << "13. ��������� ������� � ����\n";
    std::cout << "14. ��������� ������� �� �����\n";
    std::cout << "15. �����\n";
    std::cout << "�������� ��������: ";
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
            std::cout << "����� �� ���������.\n";
            return 0;
        default:
            std::cout << "�������� �����! ���������� �����.\n";
        }
    }

    return 0;
}