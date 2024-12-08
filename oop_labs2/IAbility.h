#ifndef IABILITY_H
#define IABILITY_H

class GameBoard;
class ShipManager;

class IAbility {
public:
    virtual ~IAbility() = default;
    virtual void apply(GameBoard& board, ShipManager& manager) = 0;
};

#endif