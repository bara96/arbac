//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_POLICY_H
#define ARBAC_POLICY_H

#include <utility>
#include <vector>
#include <xstring>
#include "../CA/CA.h"
#include "../CR/CR.h"
#include "../UR/UR.h"
#include "../../Controls/Utility/Utility.h"

class Policy {
private:
    std::vector<std::string> roles;
    std::vector<std::string> users;
    std::vector<UR> userRoles;
    std::vector<CR> canRevoke;
    std::vector<CA> canAssign;
    std::string goal;

public:
    Policy();

    Policy(std::vector<std::string> roles, std::vector<std::string> users,
           std::vector<UR> userRoles, std::vector<CR> canRevoke, std::vector<CA> canAssign,
           std::string goal);

    const std::vector<std::string> &getRoles() const {
        return roles;
    }

    void setRoles(const std::vector<std::string> &roleVal);

    const std::vector<std::string> &getUsers() const {
        return users;
    }

    void setUsers(const std::vector<std::string> &usersVal);

    const std::vector<UR> &getUserRoles() const {
        return userRoles;
    }

    void setUserRoles(const std::vector<UR> &userRolesVal);

    const std::vector<CR> &getCanRevoke() const {
        return canRevoke;
    }

    void setCanRevoke(const std::vector<CR> &canRevokeVal);

    const std::vector<CA> &getCanAssign() const {
        return canAssign;
    }

    void setCanAssign(const std::vector<CA> &canAssignVal);

    const std::string &getGoal() const {
        return goal;
    }

    void setGoal(const std::string &goalVal);

    void print() {
        std::cout << "Roles: " << "\n";
        Utility::printVector(roles);
        std::cout << "Users: " << "\n";
        Utility::printVector(users);
        std::cout << "UR: " << "\n";
        for (auto & value : userRoles) {
            value.print();
            cout << " ";
        }
        std::cout << "\n";
        std::cout << "CR: " << "\n";
        for (auto & value : canRevoke) {
            value.print();
            cout << " ";
        }
        std::cout << "\n";
        std::cout << "CA: " << "\n";
        for (auto & value : canAssign) {
            value.print();
            cout << " ";
        }
        std::cout << "\n";
    }
};


#endif //ARBAC_POLICY_H
