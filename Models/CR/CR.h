//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_CR_H
#define ARBAC_CR_H

#include <utility>
#include <xstring>
#include <iostream>
#include "../Rule/Rule.h"

class CR : Rule {
private:
    std::string roleAdmin;
    std::string roleToRevoke;

public:
    CR();

    CR(std::string roleAdmin, std::string roleToRevoke);

    const std::string &getRoleAdmin() const override {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal) override;

    const std::string &getRoleTarget() const override {
        return roleToRevoke;
    }

    void setRoleTarget(const std::string &roleToRevokeVal) override;

    void print() {
        std::cout << "<" << roleAdmin << "," << roleToRevoke << ">";
    }
};


#endif //ARBAC_CR_H
