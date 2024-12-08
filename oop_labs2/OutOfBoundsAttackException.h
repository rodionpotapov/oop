#ifndef OUTOFBOUNDSATTACKEXCEPTION_H
#define OUTOFBOUNDSATTACKEXCEPTION_H

#include <stdexcept>

class OutOfBoundsAttackException : public std::runtime_error {
public:
    OutOfBoundsAttackException();
};

#endif