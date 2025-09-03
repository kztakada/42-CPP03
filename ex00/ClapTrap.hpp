#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
   public:
    ClapTrap();
    ClapTrap(const std::string &name);
    ~ClapTrap();
    ClapTrap(ClapTrap const &other);
    ClapTrap &operator=(ClapTrap const &other);

    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

    unsigned int getHitPoints(void) const;
    unsigned int getEnergyPoints(void) const;
    unsigned int getAttackDamage(void) const;

   private:
    std::string _name;
    long long _hitPoints;
    long long _energyPoints;
    unsigned int _attackDamage;

    bool _canAction(void) const;
};

#endif /* CLAPTRAP_HPP */