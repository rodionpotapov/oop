#include "DoubleDamage.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include <iostream>

DoubleDamage::DoubleDamage() {}

void DoubleDamage::apply(GameBoard& board, ShipManager& manager) {
    (void)board;    // чтобы подавить предупреждение о неиспользуемом параметре
    (void)manager;
    std::cout << "Применена способность 'Двойной урон'. Следующая попадание нанесет дополнительный урон.\n";
    board.enableDoubleDamageFlag(true);
}