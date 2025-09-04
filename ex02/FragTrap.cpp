#include "FragTrap.hpp"

#include <iostream>
#include <sstream>

FragTrap::FragTrap() : ClapTrap() {
    this->_hitPoints = this->_defaultHitPoints;
    this->_energyPoints = this->_defaultEnergyPoints;
    this->_attackDamage = this->_defaultAttackDamage;
    std::stringstream ss;
    ss << "FragTrap " << this->_name << " default constructor called";
    this->_printColored(ss.str());
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
    this->_hitPoints = this->_defaultHitPoints;
    this->_energyPoints = this->_defaultEnergyPoints;
    this->_attackDamage = this->_defaultAttackDamage;
    std::stringstream ss;
    ss << "FragTrap " << this->_name << " constructor called";
    this->_printColored(ss.str());
}

FragTrap::~FragTrap() {
    std::stringstream ss;
    ss << "FragTrap " << this->_name << " destructor called";
    this->_printColored(ss.str());
}

FragTrap::FragTrap(FragTrap const &other) : ClapTrap(other) {
    std::stringstream ss;
    ss << "FragTrap " << this->_name << " Copy constructor called";
    this->_printColored(ss.str());
}

FragTrap &FragTrap::operator=(FragTrap const &other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    std::stringstream ss;
    ss << "FragTrap " << this->_name << " Copy assignment operator called";
    this->_printColored(ss.str());
    return *this;
}

void FragTrap::highFivesGuys(void) {
    std::stringstream ss;
    if (this->_canAction()) {
        this->_energyPoints--;
        ss << "FragTrap " << this->_name
           << " is requesting a positive high five!";
    } else {
        ss << "Cannot high five.";
    }
    this->_printColored(ss.str());
}

bool FragTrap::_canAction(void) const {
    if (this->_energyPoints > 0 && this->_hitPoints > 0)
        return true;

    if (this->_energyPoints <= 0 && this->_hitPoints <= 0) {
        std::cout << "\033[34m"
                     "FragTrap "
                  << this->_name << " is out of energy and hit points! "
                  << "\033[0m";

        return false;
    }

    if (this->_energyPoints <= 0) {
        std::cout << "\033[34m"
                     "FragTrap "
                  << this->_name << " has no energy left. " << "\033[0m";
    }
    if (this->_hitPoints <= 0) {
        std::cout << "\033[34m"
                     "FragTrap "
                  << this->_name << " has no hit points left. " << "\033[0m";
    }

    return false;
}

void FragTrap::_printColored(const std::string &text) const {
    std::cout << "\033[34m" << text << "\033[0m" << std::endl;
}
