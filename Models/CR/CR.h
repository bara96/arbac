//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_CR_H
#define ARBAC_CR_H

#include <utility>
#include <xstring>
#include <iostream>

class CR {
private:
    std::string roleAdmin;
    std::string roleToRevoke;

public:
    CR();

    CR(std::string roleAdmin, std::string roleToRevoke);

    const std::string &getRoleAdmin() const {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal);

    const std::string &getRoleToRevoke() const {
        return roleToRevoke;
    }

    void setRoleToRevoke(const std::string &roleToRevokeVal);

    void print() {
        std::cout << "<" << roleAdmin << "," << roleToRevoke;
    }
};


#endif //ARBAC_CR_H
