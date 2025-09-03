#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {
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
};

#endif /* SCAVTRAP_HPP */