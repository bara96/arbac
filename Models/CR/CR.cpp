//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>

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

    void setRoleAdmin(const std::string &roleAdmin) {
        CR::roleAdmin = roleAdmin;
    }

    const std::string &getRoleToRevoke() const {
        return roleToRevoke;
    }

    void setRoleToRevoke(const std::string &roleToRevoke) {
        CR::roleToRevoke = roleToRevoke;
    }
};