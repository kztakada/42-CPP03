#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
   public:
    ScavTrap();
    ScavTrap(const std::string &name);
    ~ScavTrap();
    ScavTrap(ScavTrap const &other);
    ScavTrap &operator=(ScavTrap const &other);

    void attack(const std::string &target);
    void guardGate();

   private:
    bool _canAction(void) const;
    void _printColored(const std::string &text) const;

    static const int _defaultHitPoints = 100;
    static const int _defaultEnergyPoints = 50;
    static const int _defaultAttackDamage = 20;
};

#endif /* SCAVTRAP_HPP */