#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
   public:
    FragTrap();
    FragTrap(const std::string &name);
    ~FragTrap();
    FragTrap(FragTrap const &other);
    FragTrap &operator=(FragTrap const &other);

    void highFivesGuys(void);

   private:
    bool _canAction(void) const;
    void _printColored(const std::string &text) const;
};

#endif /* FRAGTRAP_HPP */