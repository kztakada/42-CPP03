#include <cassert>
#include <iostream>
#include <limits>

#include "FragTrap.hpp"

void printColored(const std::string& text) {
    std::cout << "\033[32m" << text << "\033[0m" << std::endl;
}

const unsigned int HITPOINTS = 100;
const unsigned int ENERGYPOINTS = 100;
const unsigned int ATTACKDAMAGE = 30;

void testOrthodoxCanonicalForm() {
    FragTrap fragTrap1("FragTrap1");
    FragTrap fragTrap2("FragTrap2");

    // Assert that the named constructed object is in a valid state
    assert(fragTrap1.getHitPoints() == HITPOINTS);
    assert(fragTrap1.getEnergyPoints() == ENERGYPOINTS);
    assert(fragTrap1.getAttackDamage() == ATTACKDAMAGE);

    // Test default constructor
    FragTrap fragTrap3;

    // Test copy constructor
    FragTrap fragTrap4(fragTrap1);

    // Test copy assignment operator
    fragTrap2 = fragTrap1;

    // Assert that the objects are equal
    assert(fragTrap1.getHitPoints() == fragTrap4.getHitPoints());
    assert(fragTrap1.getEnergyPoints() == fragTrap4.getEnergyPoints());
    assert(fragTrap1.getAttackDamage() == fragTrap4.getAttackDamage());

    // Assert that the default constructed object is in a valid state
    assert(fragTrap3.getHitPoints() == HITPOINTS);
    assert(fragTrap3.getEnergyPoints() == ENERGYPOINTS);
    assert(fragTrap3.getAttackDamage() == ATTACKDAMAGE);
    printColored("Orthodox Canonical Form tests passed.");
}

void testLimitsOfAttack() {
    FragTrap fragTrap("Attacker");

    // Test attack until you run out of energy
    for (int i = 0; i < 101; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        fragTrap.attack("target");
    }

    // Assert that FragTrap is out of energy
    assert(fragTrap.getEnergyPoints() == 0);
    assert(fragTrap.getHitPoints() == HITPOINTS);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);
    printColored("Limits of Attack tests passed.");
}

void testLimitsOfRepair() {
    FragTrap fragTrap("RepairBot");

    unsigned int defaultHitPoints = fragTrap.getHitPoints();
    unsigned int repairAmount = 5;
    // Test repair until you run out of energy
    for (int i = 0; i < 100; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        fragTrap.beRepaired(repairAmount);
        assert(fragTrap.getHitPoints() ==
               defaultHitPoints + (i + 1) * repairAmount);
    }
    std::cout << "Repair attempt 101: ";
    fragTrap.beRepaired(repairAmount);

    // Assert that FragTrap is out of energy
    assert(fragTrap.getEnergyPoints() == 0);
    assert(fragTrap.getHitPoints() == defaultHitPoints + 100 * repairAmount);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------
    FragTrap fragTrap2("RepairBot2");

    // defaultHitPoints = fragTrap2.getHitPoints();
    repairAmount = std::numeric_limits<unsigned int>::max();

    // Test repair until you run out of energy
    for (int i = 0; i < 100; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        fragTrap2.beRepaired(repairAmount);
        assert(fragTrap2.getHitPoints() ==
               std::numeric_limits<unsigned int>::max());
    }
    std::cout << "Repair attempt 101: ";
    fragTrap2.beRepaired(repairAmount);

    // Assert that FragTrap is out of energy
    assert(fragTrap2.getEnergyPoints() == 0);
    assert(
        fragTrap2.getHitPoints() == std::numeric_limits<unsigned int>::max());
    assert(fragTrap2.getAttackDamage() == ATTACKDAMAGE);

    printColored("Limits of Repair tests passed.");
}

void testTakeDamage() {
    FragTrap fragTrap("DamageBot");

    int defaultHitPoints = fragTrap.getHitPoints();
    unsigned int damageAmount = 10;
    // Test 10 times of take damage
    for (int i = 0; i < 9; ++i) {
        fragTrap.takeDamage(damageAmount);
        assert(fragTrap.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
    }
    assert(fragTrap.getHitPoints() == 10);
    assert(fragTrap.getEnergyPoints() == ENERGYPOINTS);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    fragTrap.attack("target");
    assert(fragTrap.getHitPoints() == 10);
    assert(fragTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    fragTrap.takeDamage(damageAmount);
    assert(fragTrap.getHitPoints() == 0);
    assert(fragTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    fragTrap.attack("target");
    assert(fragTrap.getHitPoints() == 0);
    assert(fragTrap.getEnergyPoints() == ENERGYPOINTS - 1);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    // for no Energy and no Hitpoints------------------------------
    FragTrap fragTrap2("DamageBot2");

    defaultHitPoints = fragTrap2.getHitPoints();
    unsigned int defaultEnergyPoints = fragTrap2.getEnergyPoints();
    damageAmount = 1;
    // Test 100 times of take damage
    for (int i = 0; i < 100; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        fragTrap2.attack("target");
        std::cout << "Damage attempt " << (i + 1) << ": ";
        fragTrap2.takeDamage(damageAmount);
        assert(fragTrap2.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
        assert(fragTrap2.getEnergyPoints() == defaultEnergyPoints - (i + 1));
        assert(fragTrap2.getAttackDamage() == ATTACKDAMAGE);
    }
    fragTrap2.attack("target");
    assert(fragTrap2.getHitPoints() == 0);
    assert(fragTrap2.getEnergyPoints() == 0);
    assert(fragTrap2.getAttackDamage() == ATTACKDAMAGE);
    fragTrap2.highFivesGuys();
    assert(fragTrap2.getHitPoints() == 0);
    assert(fragTrap2.getEnergyPoints() == 0);
    assert(fragTrap2.getAttackDamage() == ATTACKDAMAGE);
    fragTrap2.beRepaired(1);
    assert(fragTrap2.getHitPoints() == 0);
    assert(fragTrap2.getEnergyPoints() == 0);
    assert(fragTrap2.getAttackDamage() == ATTACKDAMAGE);

    // use UNSIGNED_INT_MAX----------------------------------------

    FragTrap fragTrap3("DamageBot3");
    unsigned int damageAmount3 = std::numeric_limits<unsigned int>::max();

    // Test take damage until hit points are 0
    for (int i = 0; i < 10; ++i) {
        fragTrap3.takeDamage(damageAmount3);
        assert(fragTrap3.getHitPoints() == 0);
        assert(fragTrap3.getEnergyPoints() == ENERGYPOINTS);
        assert(fragTrap3.getAttackDamage() == ATTACKDAMAGE);
    }

    printColored("Take Damage tests passed.");
}

void testHighFivesGuys() {
    FragTrap fragTrap("GuardBot");

    // Test HighFivesGuys until you run out of energy
    for (int i = 0; i < 101; ++i) {
        std::cout << "High five attempt " << (i + 1) << ": ";
        fragTrap.highFivesGuys();
    }

    // Assert that FragTrap is out of energy
    assert(fragTrap.getEnergyPoints() == 0);
    assert(fragTrap.getHitPoints() == HITPOINTS);
    assert(fragTrap.getAttackDamage() == ATTACKDAMAGE);

    printColored("High Fives Guys tests passed.");
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
    testHighFivesGuys();

    return 0;
}