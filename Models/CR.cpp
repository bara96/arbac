//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>
#include <iostream>

class CR {
private:
    std::string roleAdmin;
    std::string roleToRevoke;

public:
    CR() = default;

    CR(std::string roleAdmin, std::string roleToRevoke) :
    roleAdmin(std::move(roleAdmin)),
    roleToRevoke(std::move(roleToRevoke)) {}

    const std::string &getRoleAdmin() const {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal) {
        CR::roleAdmin = roleAdminVal;
    }

    const std::string &getRoleToRevoke() const {
        return roleToRevoke;
    }

    void setRoleToRevoke(const std::string &roleToRevokeVal) {
        CR::roleToRevoke = roleToRevokeVal;
    }

    void print() {
        std::cout << "<" << roleAdmin << "," << roleToRevoke;
    }
};