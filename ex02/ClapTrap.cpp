#include "ClapTrap.hpp"

#include <iostream>
#include <limits>

ClapTrap::ClapTrap()
    : _name(""),
      _hitPoints(this->_defaultHitPoints),
      _energyPoints(this->_defaultEnergyPoints),
      _attackDamage(this->_defaultAttackDamage) {
    std::cout << "ClapTrap " << this->_name << " default constructor called"
              << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name),
      _hitPoints(this->_defaultHitPoints),
      _energyPoints(this->_defaultEnergyPoints),
      _attackDamage(this->_defaultAttackDamage) {
    std::cout << "ClapTrap " << this->_name << " constructor called"
              << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << this->_name << " destructor called"
              << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &other)
    : _name(other._name),
      _hitPoints(other._hitPoints),
      _energyPoints(other._energyPoints),
      _attackDamage(other._attackDamage) {
    std::cout << "ClapTrap " << this->_name << " Copy constructor called"
              << std::endl;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &other) {
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    std::cout << "ClapTrap " << this->_name
              << " Copy assignment operator called" << std::endl;
    return *this;
}

void ClapTrap::attack(std::string const &target) {
    if (this->_canAction()) {
        this->_energyPoints--;
        std::cout << "ClapTrap " << this->_name << " attacks " << target
                  << ", causing " << this->_attackDamage << " points of damage!"
                  << std::endl;
    } else {
        std::cout << "Cannot attack." << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    this->_hitPoints -= amount;
    if (this->_hitPoints < 0)
        this->_hitPoints = 0;
    std::cout << "ClapTrap " << this->_name << " takes " << amount
              << " points of damage! Remaining hit points: " << this->_hitPoints
              << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->_canAction()) {
        this->_energyPoints--;
        this->_hitPoints += static_cast<long long>(amount);
        if (this->_hitPoints > std::numeric_limits<unsigned int>::max())
            this->_hitPoints = std::numeric_limits<unsigned int>::max();
        std::cout << "ClapTrap " << this->_name << " is repaired by " << amount
                  << " points! Current hit points: " << this->_hitPoints
                  << std::endl;
    } else {
        std::cout << "Cannot be repaired." << std::endl;
    }
}

unsigned int ClapTrap::getHitPoints(void) const {
    return static_cast<unsigned int>(this->_hitPoints);
}

unsigned int ClapTrap::getEnergyPoints(void) const {
    return this->_energyPoints;
}

unsigned int ClapTrap::getAttackDamage(void) const {
    return this->_attackDamage;
}

bool ClapTrap::_canAction(void) const {
    if (this->_energyPoints > 0 && this->_hitPoints > 0)
        return true;

    if (this->_energyPoints <= 0 && this->_hitPoints <= 0) {
        std::cout << "ClapTrap " << this->_name
                  << " is out of energy and hit points! ";
        return false;
    }

    if (this->_energyPoints <= 0)
        std::cout << "ClapTrap " << this->_name << " has no energy left. ";
    if (this->_hitPoints <= 0)
        std::cout << "ClapTrap " << this->_name << " has no hit points left. ";

    return false;
}
