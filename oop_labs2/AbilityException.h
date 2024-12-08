#ifndef ABILITYEXCEPTION_H
#define ABILITYEXCEPTION_H

#include <stdexcept>

class NoAbilitiesException : public std::runtime_error {
public:
    NoAbilitiesException();
};

#endif