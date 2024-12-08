#include "RandomStrike.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include "Ship.h"
#include <iostream>
#include <cstdlib>

RandomStrike::RandomStrike() {}

void RandomStrike::apply(GameBoard& board, ShipManager& manager) {
    (void)board; // Подавляем предупреждение об неиспользуемом параметре, 

    std::vector<size_t> aliveShips;
    for (size_t i = 0; i < manager.getShipCount(); ++i) {
        if (!manager.getShip(i).isDestroyed()) {
            aliveShips.push_back(i);
        }
    }

    if (aliveShips.empty()) {
        std::cout << "Нет кораблей для обстрела.\n";
        return;
    }

    size_t shipIndex = aliveShips[rand() % aliveShips.size()];
    Ship& ship = manager.getShip(shipIndex);

    std::vector<size_t> viableSegments;
    for (size_t i = 0; i < ship.getLength(); ++i) {
        auto state = ship.getSegmentState(i);
        if (state == Ship::Whole || state == Ship::Damage) {
            viableSegments.push_back(i);
        }
    }

    if (viableSegments.empty()) {
        std::cout << "Выбранный корабль уже уничтожен.\n";
        return;
    }

    size_t segIndex = viableSegments[rand() % viableSegments.size()];
    ship.hitSegment(segIndex);

    std::cout << "Обстрел нанес урон кораблю " << shipIndex << " в сегмент " << segIndex << ".\n";

    if (ship.isDestroyed()) {
        std::cout << "Корабль " << shipIndex << " уничтожен! Игрок получает новую случайную способность.\n";
        manager.awardRandomAbility();
    }
}