//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_UR_H
#define ARBAC_UR_H

#include <utility>
#include <xstring>
#include <iostream>

class UR {
private:
    std::string user;
    std::string role;

public:
    UR();

    UR(std::string user, std::string role);

    const std::string &getUser() const {
        return user;
    }

    void setUser(const std::string &userVal);

    const std::string &getRole() const {
        return role;
    }

    void setRole(const std::string &roleVal);

    void print() {
        std::cout << "<" << user << "," << role << ">";
    }
};


#endif //ARBAC_UR_H
