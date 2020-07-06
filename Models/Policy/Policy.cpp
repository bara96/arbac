//
// Created by mbaratella on 04/07/2020.
//

#include "Policy.h"

Policy::Policy() = default;

Policy::Policy(std::vector<std::string> roles, std::vector<std::string> users,
        std::vector<UR> userRoles, std::vector<CR> canRevoke, std::vector<CA> canAssign,
std::string goal) :
roles(std::move(roles)),
users(std::move(users)),
userRoles(std::move(userRoles)),
canRevoke(std::move(canRevoke)),
canAssign(std::move(canAssign)),
goal(std::move(goal)) {}

void Policy::setRoles(const std::vector<std::string> &roleVal) {
    Policy::roles = roleVal;
}

void Policy::setUsers(const std::vector<std::string> &usersVal) {
    Policy::users = usersVal;
}

void Policy::setUserRoles(const std::vector<UR> &userRolesVal) {
    Policy::userRoles = userRolesVal;
}

void Policy::setCanRevoke(const std::vector<CR> &canRevokeVal) {
    Policy::canRevoke = canRevokeVal;
}

void Policy::setCanAssign(const std::vector<CA> &canAssignVal) {
    Policy::canAssign = canAssignVal;
}

void Policy::setGoal(const std::string &goalVal) {
    Policy::goal = goalVal;
}