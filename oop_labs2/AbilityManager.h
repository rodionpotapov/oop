#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include <memory>
#include <cstdlib>
#include "IAbility.h"
#include "AbilityException.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "RandomStrike.h"

class AbilityManager {
public:
    AbilityManager();
    void useAbility(GameBoard& board, ShipManager& manager);
    void addRandomAbilityToQueue();
    bool empty() const;

private:
    std::queue<std::unique_ptr<IAbility>> abilities;
};

#endif