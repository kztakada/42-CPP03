#include "ScavTrap.hpp"

#include <iostream>
#include <sstream>

ScavTrap::ScavTrap() : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::stringstream ss;
    ss << "ScavTrap " << this->_name << " default constructor called";
    this->_printColored(ss.str());
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::stringstream ss;
    ss << "ScavTrap " << this->_name << " constructor called";
    this->_printColored(ss.str());
}

ScavTrap::~ScavTrap() {
    std::stringstream ss;
    ss << "ScavTrap " << this->_name << " destructor called";
    this->_printColored(ss.str());
}

ScavTrap::ScavTrap(ScavTrap const &other) : ClapTrap(other) {
    std::stringstream ss;
    ss << "ScavTrap " << this->_name << " Copy constructor called";
    this->_printColored(ss.str());
}

ScavTrap &ScavTrap::operator=(ScavTrap const &other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    std::stringstream ss;
    ss << "ScavTrap " << this->_name << " Copy assignment operator called";
    this->_printColored(ss.str());
    return *this;
}

void ScavTrap::attack(const std::string &target) {
    std::stringstream ss;
    if (this->_canAction()) {
        this->_energyPoints--;
        ss << "ScavTrap " << this->_name << " attacks " << target
           << ", causing " << this->_attackDamage << " points of damage!";
    } else {
        ss << "Cannot attack.";
    }
    this->_printColored(ss.str());
}

void ScavTrap::guardGate() {
    std::stringstream ss;
    if (this->_canAction()) {
        this->_energyPoints--;
        ss << "ScavTrap " << this->_name << " is now in Gate Keeper mode.";
    } else {
        ss << "Cannot enter Gate Keeper mode.";
    }
    this->_printColored(ss.str());
}

bool ScavTrap::_canAction(void) const {
    if (this->_energyPoints > 0 && this->_hitPoints > 0)
        return true;

    if (this->_energyPoints <= 0 && this->_hitPoints <= 0) {
        std::cout << "\033[33m"
                     "ScavTrap "
                  << this->_name << " is out of energy and hit points! "
                  << "\033[0m";

        return false;
    }

    if (this->_energyPoints <= 0) {
        std::cout << "\033[33m"
                     "ScavTrap "
                  << this->_name << " has no energy left. " << "\033[0m";
    }
    if (this->_hitPoints <= 0) {
        std::cout << "\033[33m"
                     "ScavTrap "
                  << this->_name << " has no hit points left. " << "\033[0m";
    }

    return false;
}

void ScavTrap::_printColored(const std::string &text) const {
    std::cout << "\033[33m" << text << "\033[0m" << std::endl;
}
