#include "DiamondTrap.hpp"

#include <iostream>
#include <sstream>

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap(), _name("") {
    ClapTrap::_name = _name + "_clap_name";
    this->_hitPoints = FragTrap::_defaultHitPoints;
    this->_energyPoints = ScavTrap::_defaultEnergyPoints;
    this->_attackDamage = FragTrap::_defaultAttackDamage;
    std::stringstream ss;
    ss << "DiamondTrap " << this->_name << " default constructor called";
    this->_printColored(ss.str());
}

DiamondTrap::DiamondTrap(const std::string &name)
    : ClapTrap(name), ScavTrap(name), FragTrap(name), _name(name) {
    ClapTrap::_name = _name + "_clap_name";
    this->_hitPoints = FragTrap::_defaultHitPoints;
    this->_energyPoints = ScavTrap::_defaultEnergyPoints;
    this->_attackDamage = FragTrap::_defaultAttackDamage;
    std::stringstream ss;
    ss << "DiamondTrap " << this->_name << " constructor called";
    this->_printColored(ss.str());
}

DiamondTrap::~DiamondTrap() {
    std::stringstream ss;
    ss << "DiamondTrap " << this->_name << " destructor called";
    this->_printColored(ss.str());
}

DiamondTrap::DiamondTrap(DiamondTrap const &other) {
    if (this != &other) {
        ClapTrap::_name = other.ClapTrap::_name;
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    std::stringstream ss;
    ss << "DiamondTrap " << this->_name << " Copy constructor called";
    this->_printColored(ss.str());
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap const &other) {
    if (this != &other) {
        ClapTrap::_name = other.ClapTrap::_name;
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    std::stringstream ss;
    ss << "DiamondTrap " << this->_name << " Copy assignment operator called";
    this->_printColored(ss.str());
    return *this;
}

void DiamondTrap::attack(const std::string &target) {
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
    std::stringstream ss;
    if (this->_canAction()) {
        this->_energyPoints--;
        ss << "DiamondTrap name: " << this->_name
           << ", ClapTrap name: " << ClapTrap::_name;
    } else {
        ss << "Cannot who am I.";
    }
    this->_printColored(ss.str());
}

bool DiamondTrap::_canAction(void) const {
    if (this->_energyPoints > 0 && this->_hitPoints > 0)
        return true;

    if (this->_energyPoints <= 0 && this->_hitPoints <= 0) {
        std::cout << "\033[35m"
                     "DiamondTrap "
                  << this->_name << " is out of energy and hit points! "
                  << "\033[0m";

        return false;
    }

    if (this->_energyPoints <= 0) {
        std::cout << "\033[35m"
                     "DiamondTrap "
                  << this->_name << " has no energy left. " << "\033[0m";
    }
    if (this->_hitPoints <= 0) {
        std::cout << "\033[35m"
                     "DiamondTrap "
                  << this->_name << " has no hit points left. " << "\033[0m";
    }

    return false;
}

void DiamondTrap::_printColored(const std::string &text) const {
    std::cout << "\033[35m" << text << "\033[0m" << std::endl;
}
