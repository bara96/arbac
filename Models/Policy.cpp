//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <vector>
#include <xstring>
#include "UR.cpp"
#include "CA.cpp"
#include "CR.cpp"

class Policy {

private:
    std::vector<std::string> roles;
    std::vector<std::string> users;
    std::vector<UR> userRoles;
    std::vector<CR> canRevoke;
    std::vector<CA> canAssign;
    std::string goal;

public:
    Policy() = default;

    Policy(std::vector<std::string> roles, std::vector<std::string> users,
           std::vector<UR> userRoles, std::vector<CR> canRevoke, std::vector<CA> canAssign,
           std::string goal) :
           roles(std::move(roles)),
           users(std::move(users)),
           userRoles(std::move(userRoles)),
           canRevoke(std::move(canRevoke)),
           canAssign(std::move(canAssign)),
           goal(std::move(goal)) {}

    const std::vector<std::string> &getRoles() const {
        return roles;
    }

    void setRoles(const std::vector<std::string> &roleVal) {
        Policy::roles = roleVal;
    }

    const std::vector<std::string> &getUsers() const {
        return users;
    }

    void setUsers(const std::vector<std::string> &usersVal) {
        Policy::users = usersVal;
    }

    const std::vector<UR> &getUserRoles() const {
        return userRoles;
    }

    void setUserRoles(const std::vector<UR> &userRolesVal) {
        Policy::userRoles = userRolesVal;
    }

    const std::vector<CR> &getCanRevoke() const {
        return canRevoke;
    }

    void setCanRevoke(const std::vector<CR> &canRevokeVal) {
        Policy::canRevoke = canRevokeVal;
    }

    const std::vector<CA> &getCanAssign() const {
        return canAssign;
    }

    void setCanAssign(const std::vector<CA> &canAssignVal) {
        Policy::canAssign = canAssignVal;
    }

    const std::string &getGoal() const {
        return goal;
    }

    void setGoal(const std::string &goalVal) {
        Policy::goal = goalVal;
    }
};
