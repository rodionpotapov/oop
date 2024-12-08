#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include "Ship.h"

class AbilityManager;

class ShipManager {
public:
    ShipManager(const std::vector<size_t>& shipSizes);
    Ship& getShip(size_t index);
    bool allShipsDestroyed() const;
    size_t getShipCount() const { return ships.size(); }

    void setAbilityManager(AbilityManager* am) { abilityManager = am; }
    void awardRandomAbility();

private:
    std::vector<Ship> ships;
    AbilityManager* abilityManager = nullptr;
    void initializeShips(const std::vector<size_t>& shipSizes);
};

#endif