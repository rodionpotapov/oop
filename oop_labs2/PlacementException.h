#ifndef PLACEMENTEXCEPTION_H
#define PLACEMENTEXCEPTION_H

#include <stdexcept>

class InvalidShipPlacementException : public std::runtime_error {
public:
    InvalidShipPlacementException();
};

#endif