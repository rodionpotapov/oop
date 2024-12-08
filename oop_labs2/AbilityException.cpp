#include "AbilityException.h"

NoAbilitiesException::NoAbilitiesException()
    : std::runtime_error("Нет доступных способностей для применения.") {}