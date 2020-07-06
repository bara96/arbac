//
// Created by mbaratella on 04/07/2020.
//

#include "CR.h"

CR::CR() = default;

CR::CR(std::string roleAdmin, std::string roleToRevoke) :
roleAdmin(std::move(roleAdmin)),
roleToRevoke(std::move(roleToRevoke)) {}

void CR::setRoleAdmin(const std::string &roleAdminVal) {
    CR::roleAdmin = roleAdminVal;
}

void CR::setRoleTarget(const std::string &roleToRevokeVal) {
    CR::roleToRevoke = roleToRevokeVal;
}