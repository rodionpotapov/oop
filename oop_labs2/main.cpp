#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ShipManager.h"
#include "GameBoard.h"
#include "BoardRenderer.h"
#include "AbilityManager.h"
#include "PlacementException.h"
#include "OutOfBoundsAttackException.h"
#include "AbilityException.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try {
        std::vector<size_t> shipSizes = {1, 2, 3, 4};
        ShipManager manager(shipSizes);
        GameBoard board(10, 10);
        AbilityManager abilityManager;

        manager.setAbilityManager(&abilityManager);

        // Используем две способности
        abilityManager.useAbility(board, manager);
        abilityManager.useAbility(board, manager);

        // Размещаем корабль
        Ship& ship1 = manager.getShip(1);
        board.placeShip(ship1, 5, 5, Ship::Vertical, &manager);

        // Атакуем клетку (5,7)
        board.attack(5, 7, manager);

        // Отображаем игровое поле
        BoardRenderer renderer(board);
        std::cout << "Игровое поле после атаки:" << std::endl;
        renderer.render();

        // Проверка исключения атаки за пределами
        try {
            board.attack(100, 100, manager);
        } catch (const OutOfBoundsAttackException& e) {
            std::cout << "Исключение при атаке: " << e.what() << std::endl;
        }

    } catch (const NoAbilitiesException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const InvalidShipPlacementException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const OutOfBoundsAttackException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}