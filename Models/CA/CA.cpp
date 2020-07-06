//
// Created by mbaratella on 04/07/2020.
//

#include "CA.h"

#include <utility>


CA::CA() = default;

CA::CA(std::string roleAdmin, std::vector<std::string> positiveConditions,
        std::vector<std::string> negativeConditions, std::string roleToAssign) :
roleAdmin(std::move(roleAdmin)),
positiveConditions(std::move(positiveConditions)),
negativeConditions(std::move(negativeConditions)),
roleToAssign(std::move(roleToAssign)) {}

void CA::setRoleAdmin(const std::string &roleAdminVal) {
    CA::roleAdmin = roleAdminVal;
}

void CA::setPositiveConditions(const std::vector<std::string> &positiveConditionsVal) {
    CA::positiveConditions = positiveConditionsVal;
}

void CA::setNegativeConditions(const std::vector<std::string> &negativeConditionsVal) {
    CA::negativeConditions = negativeConditionsVal;
}

void CA::setRoleTarget(const std::string &roleToAssignVal) {
    CA::roleToAssign = roleToAssignVal;
}