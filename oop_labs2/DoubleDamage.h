#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "IAbility.h"

class DoubleDamage : public IAbility {
public:
    DoubleDamage();
    void apply(GameBoard& board, ShipManager& manager) override;
};

#endif