//
// Created by mbaratella on 04/07/2020.
//

#include <iostream>
#include "CA.h"


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

void CA::setRoleToAssign(const std::string &roleToAssignVal) {
    CA::roleToAssign = roleToAssignVal;
}

void CA::print() {
    bool i=false;
    std::cout << "<" << roleAdmin << ",";
    for (auto & value : positiveConditions) {
        if(i)
            std::cout << "&" ;
        std::cout << std::string(value);
        i = true;
    }
    i = false;
    for (auto & value : negativeConditions) {
        if(i)
            std::cout << "&" ;
        std::cout << "-" << value;
        i = true;
    }
    std::cout << "," << roleToAssign << ">";
}