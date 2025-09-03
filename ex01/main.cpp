#include <cassert>
#include <iostream>
#include <limits>

#include "ScavTrap.hpp"

void printColored(const std::string& text) {
    std::cout << "\033[32m" << text << "\033[0m" << std::endl;
}

const unsigned int HITPOINTS = 100;
const unsigned int ENERGYPOINTS = 50;
const unsigned int ATTACKDAMAGE = 20;

void testOrthodoxCanonicalForm() {
    ScavTrap scavTrap1("ScavTrap1");
    ScavTrap scavTrap2("ScavTrap2");

    // Assert that the named constructed object is in a valid state
    assert(scavTrap1.getHitPoints() == HITPOINTS);
    assert(scavTrap1.getEnergyPoints() == ENERGYPOINTS);
    assert(scavTrap1.getAttackDamage() == ATTACKDAMAGE);

    // Test default constructor
    ScavTrap scavTrap3;

    // Test copy constructor
    ScavTrap scavTrap4(scavTrap1);

    // Test copy assignment operator
    scavTrap2 = scavTrap1;

    // Assert that the objects are equal
    assert(scavTrap1.getHitPoints() == scavTrap4.getHitPoints());
    assert(scavTrap1.getEnergyPoints() == scavTrap4.getEnergyPoints());
    assert(scavTrap1.getAttackDamage() == scavTrap4.getAttackDamage());

    // Assert that the default constructed object is in a valid state
    assert(scavTrap3.getHitPoints() == HITPOINTS);
    assert(scavTrap3.getEnergyPoints() == ENERGYPOINTS);
    assert(scavTrap3.getAttackDamage() == ATTACKDAMAGE);
    printColored("Orthodox Canonical Form tests passed.");
}

void testLimitsOfAttack() {
    ScavTrap scavTrap("Attacker");

    // Test attack until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        scavTrap.attack("target");
    }

    // Assert that ScavTrap is out of energy
    assert(scavTrap.getEnergyPoints() == 0);
    assert(scavTrap.getHitPoints() == HITPOINTS);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);
    printColored("Limits of Attack tests passed.");
}

void testLimitsOfRepair() {
    ScavTrap scavTrap("RepairBot");

    unsigned int defaultHitPoints = scavTrap.getHitPoints();
    unsigned int repairAmount = 5;
    // Test repair until you run out of energy
    for (int i = 0; i < 50; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        scavTrap.beRepaired(repairAmount);
        assert(scavTrap.getHitPoints() ==
               defaultHitPoints + (i + 1) * repairAmount);
    }
    std::cout << "Repair attempt 51: ";
    scavTrap.beRepaired(repairAmount);

    // Assert that ScavTrap is out of energy
    assert(scavTrap.getEnergyPoints() == 0);
    assert(scavTrap.getHitPoints() == defaultHitPoints + 50 * repairAmount);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------
    ScavTrap scavTrap2("RepairBot2");

    // defaultHitPoints = scavTrap2.getHitPoints();
    repairAmount = std::numeric_limits<unsigned int>::max();

    // Test repair until you run out of energy
    for (int i = 0; i < 50; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        scavTrap2.beRepaired(repairAmount);
        assert(scavTrap2.getHitPoints() ==
               std::numeric_limits<unsigned int>::max());
    }
    std::cout << "Repair attempt 51: ";
    scavTrap2.beRepaired(repairAmount);

    // Assert that ScavTrap is out of energy
    assert(scavTrap2.getEnergyPoints() == 0);
    assert(
        scavTrap2.getHitPoints() == std::numeric_limits<unsigned int>::max());
    assert(scavTrap2.getAttackDamage() == ATTACKDAMAGE);

    printColored("Limits of Repair tests passed.");
}

void testTakeDamage() {
    ScavTrap scavTrap("DamageBot");

    int defaultHitPoints = scavTrap.getHitPoints();
    unsigned int damageAmount = 10;
    // Test 10 times of take damage
    for (int i = 0; i < 9; ++i) {
        scavTrap.takeDamage(damageAmount);
        assert(scavTrap.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
    }
    assert(scavTrap.getHitPoints() == 10);
    assert(scavTrap.getEnergyPoints() == ENERGYPOINTS);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    scavTrap.attack("target");
    assert(scavTrap.getHitPoints() == 10);
    assert(scavTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    scavTrap.takeDamage(damageAmount);
    assert(scavTrap.getHitPoints() == 0);
    assert(scavTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    scavTrap.attack("target");
    assert(scavTrap.getHitPoints() == 0);
    assert(scavTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    // for no Energy and no Hitpoints------------------------------
    ScavTrap scavTrap2("DamageBot2");

    defaultHitPoints = scavTrap2.getHitPoints();
    unsigned int defaultEnergyPoints = scavTrap2.getEnergyPoints();
    damageAmount = 2;
    // Test 50 times of take damage
    for (int i = 0; i < 50; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        scavTrap2.attack("target");
        std::cout << "Damage attempt " << (i + 1) << ": ";
        scavTrap2.takeDamage(damageAmount);
        assert(scavTrap2.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
        assert(scavTrap2.getEnergyPoints() == defaultEnergyPoints - (i + 1));
        assert(scavTrap2.getAttackDamage() == ATTACKDAMAGE);
    }
    scavTrap2.attack("target");
    assert(scavTrap2.getHitPoints() == 0);
    assert(scavTrap2.getEnergyPoints() == 0);
    assert(scavTrap2.getAttackDamage() == ATTACKDAMAGE);
    scavTrap2.guardGate();
    assert(scavTrap2.getHitPoints() == 0);
    assert(scavTrap2.getEnergyPoints() == 0);
    assert(scavTrap2.getAttackDamage() == ATTACKDAMAGE);
    scavTrap2.beRepaired(1);
    assert(scavTrap2.getHitPoints() == 0);
    assert(scavTrap2.getEnergyPoints() == 0);
    assert(scavTrap2.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------

    ScavTrap scavTrap3("DamageBot3");
    unsigned int damageAmount3 = std::numeric_limits<unsigned int>::max();

    // Test take damage until hit points are 0
    for (int i = 0; i < 10; ++i) {
        scavTrap3.takeDamage(damageAmount3);
        assert(scavTrap3.getHitPoints() == 0);
        assert(scavTrap3.getEnergyPoints() == ENERGYPOINTS);
        assert(scavTrap3.getAttackDamage() == ATTACKDAMAGE);
    }

    printColored("Take Damage tests passed.");
}

void testGuardGate() {
    ScavTrap scavTrap("GuardBot");

    // Test GuardGate until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "Guard attempt " << (i + 1) << ": ";
        scavTrap.guardGate();
    }

    // Assert that ScavTrap is out of energy
    assert(scavTrap.getEnergyPoints() == 0);
    assert(scavTrap.getHitPoints() == HITPOINTS);
    assert(scavTrap.getAttackDamage() == ATTACKDAMAGE);

    printColored("Guard Gate tests passed.");
}

int main() {
    std::cout << "-------------------------------------" << std::endl;
    testOrthodoxCanonicalForm();
    std::cout << "-------------------------------------" << std::endl;
    testLimitsOfAttack();
    std::cout << "-------------------------------------" << std::endl;
    testLimitsOfRepair();
    std::cout << "-------------------------------------" << std::endl;
    testTakeDamage();
    std::cout << "-------------------------------------" << std::endl;
    testGuardGate();

    return 0;
}