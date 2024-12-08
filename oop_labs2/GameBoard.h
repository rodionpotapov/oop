#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <utility>
#include "Ship.h"
#include "OutOfBoundsAttackException.h"
#include "PlacementException.h"

class ShipManager;

class GameBoard {
public:
    enum CellStatus { Unknown, Empty, ShipCell, HitShipCell }; // Добавлено HitShipCell

    GameBoard(size_t width, size_t height);
    GameBoard(const GameBoard& other);
    GameBoard(GameBoard&& other) noexcept;
    GameBoard& operator=(const GameBoard& other);
    GameBoard& operator=(GameBoard&& other) noexcept;

    CellStatus getCellStatus(size_t x, size_t y) const;
    size_t getWidth() const;
    size_t getHeight() const;

    bool placeShip(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation, ShipManager* manager = nullptr);
    bool attack(size_t x, size_t y, ShipManager& manager);

    void enableDoubleDamageFlag(bool val);

private:
    size_t width, height;
    std::vector<std::vector<CellStatus>> grid;
    bool doubleDamageNextHit = false;

    std::vector<std::vector<std::pair<int, int>>> shipMapping; // К какому кораблю и сегменту относится клетка

    bool canPlaceShip(const Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) const;
    void fillShipMapping(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation, ShipManager* manager);
};

#endif