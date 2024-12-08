#ifndef RANDOMSTRIKE_H
#define RANDOMSTRIKE_H

#include "IAbility.h"

class RandomStrike : public IAbility {
public:
    RandomStrike();
    void apply(GameBoard& board, ShipManager& manager) override;
};

#endif