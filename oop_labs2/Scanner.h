#ifndef SCANNER_H
#define SCANNER_H

#include "IAbility.h"

class Scanner : public IAbility {
public:
    Scanner();
    void apply(GameBoard& board, ShipManager& manager) override;
};

#endif