#include "GameBoard.h"
#include "ShipManager.h"
#include <stdexcept>
#include <iostream>

GameBoard::GameBoard(size_t width, size_t height)
    : width(width), height(height), grid(height, std::vector<CellStatus>(width, Unknown)),
      shipMapping(height, std::vector<std::pair<int, int>>(width, std::make_pair(-1, -1))) {}

GameBoard::GameBoard(const GameBoard& other)
    : width(other.width), height(other.height), grid(other.grid), doubleDamageNextHit(other.doubleDamageNextHit),
      shipMapping(other.shipMapping) {}

GameBoard::GameBoard(GameBoard&& other) noexcept
    : width(other.width), height(other.height), grid(std::move(other.grid)),
      doubleDamageNextHit(other.doubleDamageNextHit), shipMapping(std::move(other.shipMapping)) {
    other.width = 0;
    other.height = 0;
    other.doubleDamageNextHit = false;
}

GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    grid = other.grid;
    doubleDamageNextHit = other.doubleDamageNextHit;
    shipMapping = other.shipMapping;
    return *this;
}

GameBoard& GameBoard::operator=(GameBoard&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    grid = std::move(other.grid);
    doubleDamageNextHit = other.doubleDamageNextHit;
    shipMapping = std::move(other.shipMapping);

    other.width = 0;
    other.height = 0;
    other.doubleDamageNextHit = false;

    return *this;
}

GameBoard::CellStatus GameBoard::getCellStatus(size_t x, size_t y) const {
    if (x >= width || y >= height) {
        throw std::out_of_range("Неверные координаты клетки.");
    }
    return grid[y][x];
}

size_t GameBoard::getWidth() const {
    return width;
}

size_t GameBoard::getHeight() const {
    return height;
}

void GameBoard::enableDoubleDamageFlag(bool val) {
    doubleDamageNextHit = val;
}

bool GameBoard::placeShip(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation, ShipManager* manager) {
    if (!canPlaceShip(ship, startX, startY, orientation)) {
        throw InvalidShipPlacementException();
    }
    size_t length = ship.getLength();
    for (size_t i = 0; i < length; ++i) {
        if (orientation == Ship::Horizontal) {
            grid[startY][startX + i] = ShipCell;
        } else {
            grid[startY + i][startX] = ShipCell;
        }
    }
    fillShipMapping(ship, startX, startY, orientation, manager);
    return true;
}

bool GameBoard::attack(size_t x, size_t y, ShipManager& manager) {
    if (x >= width || y >= height) {
        throw OutOfBoundsAttackException();
    }

    if (grid[y][x] == ShipCell || grid[y][x] == HitShipCell) {
        auto [shipIndex, segmentIndex] = shipMapping[y][x];
        if (shipIndex >= 0 && segmentIndex >= 0) {
            Ship& ship = manager.getShip(static_cast<size_t>(shipIndex));
            ship.hitSegment(static_cast<size_t>(segmentIndex));

            // Обновляем состояние клетки в зависимости от состояния сегмента корабля
            auto segmentState = ship.getSegmentState(static_cast<size_t>(segmentIndex));
            if (segmentState == Ship::Damage) {
                grid[y][x] = HitShipCell; // Корабль повреждён
            } else if (segmentState == Ship::Destroyed) {
                grid[y][x] = HitShipCell; // Корабль уничтожен
            }

            // Двойной урон (если активирован)
            if (doubleDamageNextHit && segmentState != Ship::Destroyed) {
                ship.hitSegment(static_cast<size_t>(segmentIndex));
                std::cout << "Дополнительный урон нанесен!\n";
                doubleDamageNextHit = false;
            }

            // Если корабль полностью уничтожен, добавляем способность
            if (ship.isDestroyed()) {
                manager.awardRandomAbility();
            }

            std::cout << "Попадание по кораблю " << shipIndex << ", сегмент " << segmentIndex << "!\n";
            return true;
        }
    }

    grid[y][x] = Empty; // Клетка становится пустой, если выстрел мимо
    std::cout << "Мимо!\n";
    return false;
}

bool GameBoard::canPlaceShip(const Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) const {
    size_t length = ship.getLength();
    if (orientation == Ship::Horizontal) {
        if (startX + length > width) return false;
        for (size_t i = 0; i < length; ++i) {
            if (grid[startY][startX + i] != Unknown) return false;
        }
        for (size_t i = 0; i < length; ++i) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = (int)startX + (int)i + dx;
                    int ny = (int)startY + dy;
                    if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
                        if (grid[ny][nx] == ShipCell) {
                            return false;
                        }
                    }
                }
            }
        }
    } else { // Вертикальная ориентация
        if (startY + length > height) return false;
        for (size_t i = 0; i < length; ++i) {
            if (grid[startY + i][startX] != Unknown) return false;
        }
        for (size_t i = 0; i < length; ++i) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = (int)startX + dx;
                    int ny = (int)startY + (int)i + dy;
                    if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
                        if (grid[ny][nx] == ShipCell) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GameBoard::fillShipMapping(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation, ShipManager* manager) {
    if (manager) {
        int shipIndex = -1;
        for (size_t i = 0; i < manager->getShipCount(); ++i) {
            if (&manager->getShip(i) == &ship) {
                shipIndex = static_cast<int>(i);
                break;
            }
        }

        if (shipIndex != -1) {
            size_t length = ship.getLength();
            for (size_t i = 0; i < length; ++i) {
                size_t x = startX + (orientation == Ship::Horizontal ? i : 0);
                size_t y = startY + (orientation == Ship::Vertical ? i : 0);
                shipMapping[y][x] = std::make_pair(shipIndex, static_cast<int>(i));
            }
        }
    }
}