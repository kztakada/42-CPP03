#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
   public:
    ClapTrap();
    ClapTrap(const std::string &name);
    virtual ~ClapTrap();
    ClapTrap(ClapTrap const &other);
    ClapTrap &operator=(ClapTrap const &other);

    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

    unsigned int getHitPoints(void) const;
    unsigned int getEnergyPoints(void) const;
    unsigned int getAttackDamage(void) const;

   protected:
    std::string _name;
    long long _hitPoints;
    long long _energyPoints;
    unsigned int _attackDamage;

   private:
    bool _canAction(void) const;

    static const int _defaultHitPoints = 10;
    static const int _defaultEnergyPoints = 10;
    static const int _defaultAttackDamage = 0;
};

#endif /* CLAPTRAP_HPP */