#include "PlacementException.h"

InvalidShipPlacementException::InvalidShipPlacementException()
    : std::runtime_error("Неверное размещение корабля (касание или пересечение с другим кораблем).") {}