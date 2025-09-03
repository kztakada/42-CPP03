#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include <string>

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
   public:
    DiamondTrap();
    DiamondTrap(const std::string &name);
    ~DiamondTrap();
    DiamondTrap(DiamondTrap const &other);
    DiamondTrap &operator=(DiamondTrap const &other);

    void attack(const std::string &target);
    void whoAmI();

   private:
    std::string _name;
    bool _canAction(void) const;
    void _printColored(const std::string &text) const;
};

#endif /* DIAMONDTRAP_HPP */