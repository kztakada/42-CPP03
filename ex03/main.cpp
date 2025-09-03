#include <cassert>
#include <iostream>
#include <limits>

#include "DiamondTrap.hpp"

void printColored(const std::string& text) {
    std::cout << "\033[32m" << text << "\033[0m" << std::endl;
}

const unsigned int HITPOINTS = 100;
const unsigned int ENERGYPOINTS = 50;
const unsigned int ATTACKDAMAGE = 30;

void testOrthodoxCanonicalForm() {
    DiamondTrap diamondTrap1("DiamondTrap1");
    DiamondTrap diamondTrap2("DiamondTrap2");

    // Assert that the named constructed object is in a valid state
    assert(diamondTrap1.getHitPoints() == HITPOINTS);
    assert(diamondTrap1.getEnergyPoints() == ENERGYPOINTS);
    std::cout << diamondTrap1.getAttackDamage() << std::endl;
    assert(diamondTrap1.getAttackDamage() == ATTACKDAMAGE);

    // Test default constructor
    DiamondTrap diamondTrap3;

    // Test copy constructor
    DiamondTrap diamondTrap4(diamondTrap1);

    // Test copy assignment operator
    diamondTrap2 = diamondTrap1;

    // Assert that the objects are equal
    assert(diamondTrap1.getHitPoints() == diamondTrap4.getHitPoints());
    assert(diamondTrap1.getEnergyPoints() == diamondTrap4.getEnergyPoints());
    assert(diamondTrap1.getAttackDamage() == diamondTrap4.getAttackDamage());

    // Assert that the default constructed object is in a valid state
    assert(diamondTrap3.getHitPoints() == HITPOINTS);
    assert(diamondTrap3.getEnergyPoints() == ENERGYPOINTS);
    assert(diamondTrap3.getAttackDamage() == ATTACKDAMAGE);
    printColored("Orthodox Canonical Form tests passed.");
}

void testLimitsOfAttack() {
    DiamondTrap diamondTrap("Attacker");

    // Test attack until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        diamondTrap.attack("target");
    }

    // Assert that DiamondTrap is out of energy
    assert(diamondTrap.getEnergyPoints() == 0);
    assert(diamondTrap.getHitPoints() == HITPOINTS);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);
    printColored("Limits of Attack tests passed.");
}

void testLimitsOfRepair() {
    DiamondTrap diamondTrap("RepairBot");

    unsigned int defaultHitPoints = diamondTrap.getHitPoints();
    unsigned int repairAmount = 5;
    // Test repair until you run out of energy
    for (int i = 0; i < 50; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        diamondTrap.beRepaired(repairAmount);
        assert(diamondTrap.getHitPoints() ==
               defaultHitPoints + (i + 1) * repairAmount);
    }
    std::cout << "Repair attempt 51: ";
    diamondTrap.beRepaired(repairAmount);

    // Assert that DiamondTrap is out of energy
    assert(diamondTrap.getEnergyPoints() == 0);
    assert(diamondTrap.getHitPoints() == defaultHitPoints + 50 * repairAmount);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------
    DiamondTrap diamondTrap2("RepairBot2");

    // defaultHitPoints = diamondTrap2.getHitPoints();
    repairAmount = std::numeric_limits<unsigned int>::max();

    // Test repair until you run out of energy
    for (int i = 0; i < 50; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        diamondTrap2.beRepaired(repairAmount);
        assert(diamondTrap2.getHitPoints() ==
               std::numeric_limits<unsigned int>::max());
    }
    std::cout << "Repair attempt 51: ";
    diamondTrap2.beRepaired(repairAmount);

    // Assert that DiamondTrap is out of energy
    assert(diamondTrap2.getEnergyPoints() == 0);
    assert(diamondTrap2.getHitPoints() ==
           std::numeric_limits<unsigned int>::max());
    assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);

    printColored("Limits of Repair tests passed.");
}

void testTakeDamage() {
    DiamondTrap diamondTrap("DamageBot");

    int defaultHitPoints = diamondTrap.getHitPoints();
    unsigned int damageAmount = 10;
    // Test 10 times of take damage
    for (int i = 0; i < 9; ++i) {
        diamondTrap.takeDamage(damageAmount);
        assert(diamondTrap.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
    }
    assert(diamondTrap.getHitPoints() == 10);
    assert(diamondTrap.getEnergyPoints() == ENERGYPOINTS);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    diamondTrap.attack("target");
    assert(diamondTrap.getHitPoints() == 10);
    assert(diamondTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    diamondTrap.takeDamage(damageAmount);
    assert(diamondTrap.getHitPoints() == 0);
    assert(diamondTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    diamondTrap.attack("target");
    assert(diamondTrap.getHitPoints() == 0);
    assert(diamondTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    // for no Energy and no Hitpoints------------------------------
    DiamondTrap diamondTrap2("DamageBot2");

    defaultHitPoints = diamondTrap2.getHitPoints();
    unsigned int defaultEnergyPoints = diamondTrap2.getEnergyPoints();
    damageAmount = 2;
    // Test 50 times of take damage
    for (int i = 0; i < 50; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        diamondTrap2.attack("target");
        std::cout << "Damage attempt " << (i + 1) << ": ";
        diamondTrap2.takeDamage(damageAmount);
        assert(diamondTrap2.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
        assert(diamondTrap2.getEnergyPoints() == defaultEnergyPoints - (i + 1));
        assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);
    }
    diamondTrap2.attack("target");
    assert(diamondTrap2.getHitPoints() == 0);
    assert(diamondTrap2.getEnergyPoints() == 0);
    assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);
    diamondTrap2.highFivesGuys();
    assert(diamondTrap2.getHitPoints() == 0);
    assert(diamondTrap2.getEnergyPoints() == 0);
    assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);
    diamondTrap2.beRepaired(1);
    assert(diamondTrap2.getHitPoints() == 0);
    assert(diamondTrap2.getEnergyPoints() == 0);
    assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);
    diamondTrap2.whoAmI();
    assert(diamondTrap2.getHitPoints() == 0);
    assert(diamondTrap2.getEnergyPoints() == 0);
    assert(diamondTrap2.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------

    DiamondTrap diamondTrap3("DamageBot3");
    unsigned int damageAmount3 = std::numeric_limits<unsigned int>::max();

    // Test take damage until hit points are 0
    for (int i = 0; i < 10; ++i) {
        diamondTrap3.takeDamage(damageAmount3);
        assert(diamondTrap3.getHitPoints() == 0);
        assert(diamondTrap3.getEnergyPoints() == ENERGYPOINTS);
        assert(diamondTrap3.getAttackDamage() == ATTACKDAMAGE);
    }

    printColored("Take Damage tests passed.");
}

void testGuardGate() {
    DiamondTrap fragTrap("GuardBot");

    // Test GuardGate until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "Guard attempt " << (i + 1) << ": ";
        fragTrap.guardGate();
    }

    // Assert that DiamondTrap is out of energy
    assert(fragTrap.getEnergyPoints() == 0);
    assert(fragTrap.getHitPoints() == HITPOINTS);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    printColored("Guard Gate tests passed.");
}

void testHighFivesGuys() {
    DiamondTrap diamondTrap("HighFivesBot");

    // Test HighFivesGuys until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "High five attempt " << (i + 1) << ": ";
        diamondTrap.highFivesGuys();
    }

    // Assert that DiamondTrap is out of energy
    assert(diamondTrap.getEnergyPoints() == 0);
    assert(diamondTrap.getHitPoints() == HITPOINTS);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    printColored("High Fives Guys tests passed.");
}

void testWhoAmI() {
    DiamondTrap diamondTrap("WhoAmIBot");

    // Test WhoAmI until you run out of energy
    for (int i = 0; i < 51; ++i) {
        std::cout << "WhoAmI attempt " << (i + 1) << ": ";
        diamondTrap.whoAmI();
    }

    // Assert that DiamondTrap is out of energy
    assert(diamondTrap.getEnergyPoints() == 0);
    assert(diamondTrap.getHitPoints() == HITPOINTS);
    assert(diamondTrap.getAttackDamage() == ATTACKDAMAGE);

    printColored("Who Am I tests passed.");
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
    std::cout << "-------------------------------------" << std::endl;
    testHighFivesGuys();
    std::cout << "-------------------------------------" << std::endl;
    testWhoAmI();

    return 0;
}