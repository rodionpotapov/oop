#include "OutOfBoundsAttackException.h"

OutOfBoundsAttackException::OutOfBoundsAttackException()
    : std::runtime_error("Атака выходит за границы поля.") {}