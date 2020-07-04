//
// Created by mbaratella on 04/07/2020.
//

#include "UR.h"

UR::UR() = default;

UR::UR(std::string user, std::string role) : user(std::move(user)), role(std::move(role)) {}

void UR::setUser(const std::string &userVal) {
    UR::user = userVal;
}

void UR::setRole(const std::string &roleVal) {
    UR::role = roleVal;
}