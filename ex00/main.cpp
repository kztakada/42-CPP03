#include <cassert>
#include <iostream>
#include <limits>

#include "ClapTrap.hpp"

void printColored(const std::string& text) {
    std::cout << "\033[32m" << text << "\033[0m" << std::endl;
}

void testOrthodoxCanonicalForm() {
    ClapTrap claptrap1("ClapTrap1");
    ClapTrap claptrap2("ClapTrap2");

    // Assert that the named constructed object is in a valid state
    assert(claptrap1.getHitPoints() == 10);
    assert(claptrap1.getEnergyPoints() == 10);
    assert(claptrap1.getAttackDamage() == 0);

    // Test default constructor
    ClapTrap claptrap3;

    // Test copy constructor
    ClapTrap claptrap4(claptrap1);

    // Test copy assignment operator
    claptrap2 = claptrap1;

    // Assert that the objects are equal
    assert(claptrap1.getHitPoints() == claptrap4.getHitPoints());
    assert(claptrap1.getEnergyPoints() == claptrap4.getEnergyPoints());
    assert(claptrap1.getAttackDamage() == claptrap4.getAttackDamage());

    // Assert that the default constructed object is in a valid state
    assert(claptrap3.getHitPoints() == 10);
    assert(claptrap3.getEnergyPoints() == 10);
    assert(claptrap3.getAttackDamage() == 0);
    printColored("Orthodox Canonical Form tests passed.");
}

void testLimitsOfAttack() {
    ClapTrap claptrap("Attacker");

    // Test attack until you run out of energy
    for (int i = 0; i < 11; ++i) {
        std::cout << "Attack attempt " << (i + 1) << ": ";
        claptrap.attack("target");
    }

    // Assert that ClapTrap is out of energy
    assert(claptrap.getEnergyPoints() == 0);
    assert(claptrap.getHitPoints() == 10);
    assert(claptrap.getAttackDamage() == 0);
    printColored("Limits of Attack tests passed.");
}

void testLimitsOfRepair() {
    ClapTrap claptrap("RepairBot");

    unsigned int defaultHitPoints = claptrap.getHitPoints();
    unsigned int repairAmount = 5;
    // Test repair until you run out of energy
    for (int i = 0; i < 10; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        claptrap.beRepaired(repairAmount);
        assert(claptrap.getHitPoints() ==
               defaultHitPoints + (i + 1) * repairAmount);
    }
    std::cout << "Repair attempt 11: ";
    claptrap.beRepaired(repairAmount);

    // Assert that ClapTrap is out of energy
    assert(claptrap.getEnergyPoints() == 0);
    assert(claptrap.getHitPoints() == defaultHitPoints + 10 * repairAmount);
    assert(claptrap.getAttackDamage() == 0);

    // use UNSIGNED_INT_MAX----------------------------------------
    ClapTrap claptrap2("RepairBot2");

    // defaultHitPoints = claptrap2.getHitPoints();
    repairAmount = std::numeric_limits<unsigned int>::max();

    // Test repair until you run out of energy
    for (int i = 0; i < 10; ++i) {
        std::cout << "Repair attempt " << (i + 1) << ": ";
        claptrap2.beRepaired(repairAmount);
        assert(claptrap2.getHitPoints() ==
               std::numeric_limits<unsigned int>::max());
    }
    std::cout << "Repair attempt 11: ";
    claptrap2.beRepaired(repairAmount);

    // Assert that ClapTrap is out of energy
    assert(claptrap2.getEnergyPoints() == 0);
    assert(
        claptrap2.getHitPoints() == std::numeric_limits<unsigned int>::max());
    assert(claptrap2.getAttackDamage() == 0);

    printColored("Limits of Repair tests passed.");
}

void testTakeDamage() {
    ClapTrap claptrap("DamageBot");

    int defaultHitPoints = claptrap.getHitPoints();
    unsigned int damageAmount = 1;
    // Test 10 times of take damage
    for (int i = 0; i < 9; ++i) {
        claptrap.takeDamage(damageAmount);
        assert(claptrap.getHitPoints() ==
               defaultHitPoints - (i + 1) * damageAmount);
    }
    assert(claptrap.getHitPoints() == 1);
    assert(claptrap.getEnergyPoints() == 10);
    assert(claptrap.getAttackDamage() == 0);

    claptrap.attack("target");
    assert(claptrap.getHitPoints() == 1);
    assert(claptrap.getEnergyPoints() == 9);
    assert(claptrap.getAttackDamage() == 0);

    claptrap.takeDamage(damageAmount);
    assert(claptrap.getHitPoints() == 0);
    assert(claptrap.getEnergyPoints() == 9);
    assert(claptrap.getAttackDamage() == 0);

    claptrap.attack("target");
    assert(claptrap.getHitPoints() == 0);
    assert(claptrap.getEnergyPoints() == 9);
    assert(claptrap.getAttackDamage() == 0);

    // use UNSIGNED_INT_MAX----------------------------------------

    ClapTrap claptrap2("DamageBot2");
    unsigned int damageAmount2 = std::numeric_limits<unsigned int>::max();

    // Test take damage until hit points are 0
    for (int i = 0; i < 10; ++i) {
        claptrap2.takeDamage(damageAmount2);
        assert(claptrap2.getHitPoints() == 0);
        assert(claptrap2.getEnergyPoints() == 10);
        assert(claptrap2.getAttackDamage() == 0);
    }

    printColored("Take Damage tests passed.");
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

    return 0;
}