#include "AbilityManager.h"

AbilityManager::AbilityManager() {
    std::vector<std::unique_ptr<IAbility>> allAbilities;
    allAbilities.push_back(std::make_unique<DoubleDamage>());
    allAbilities.push_back(std::make_unique<Scanner>());
    allAbilities.push_back(std::make_unique<RandomStrike>());

    for (int i = 0; i < 3; ++i) {
        int r = rand() % (int)allAbilities.size();
        abilities.push(std::move(allAbilities[r]));
        allAbilities.erase(allAbilities.begin() + r);
    }
}

void AbilityManager::useAbility(GameBoard& board, ShipManager& manager) {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }
    std::unique_ptr<IAbility> ability = std::move(abilities.front());
    abilities.pop();
    ability->apply(board, manager);
}

void AbilityManager::addRandomAbilityToQueue() {
    int r = rand() % 3;
    switch (r) {
        case 0:
            abilities.push(std::make_unique<DoubleDamage>());
            break;
        case 1:
            abilities.push(std::make_unique<Scanner>());
            break;
        case 2:
            abilities.push(std::make_unique<RandomStrike>());
            break;
    }
}

bool AbilityManager::empty() const {
    return abilities.empty();
}