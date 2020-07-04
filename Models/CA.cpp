//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>
#include <vector>
#include <iostream>

class CA {
private:
    std::string roleAdmin;
    std::vector<std::string> positiveConditions;
    std::vector<std::string> negativeConditions;
    std::string roleToAssign;

public:
    CA() = default;

    CA(std::string roleAdmin, std::vector<std::string> positiveConditions,
       std::vector<std::string> negativeConditions, std::string roleToAssign) :
       roleAdmin(std::move(roleAdmin)),
       positiveConditions(std::move(positiveConditions)),
       negativeConditions(std::move(negativeConditions)),
       roleToAssign(std::move(roleToAssign)) {}

    const std::string &getRoleAdmin() const {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal) {
        CA::roleAdmin = roleAdminVal;
    }

    const std::vector<std::string> &getPositiveConditions() const {
        return positiveConditions;
    }

    void setPositiveConditions(const std::vector<std::string> &positiveConditionsVal) {
        CA::positiveConditions = positiveConditionsVal;
    }

    const std::vector<std::string> &getNegativeConditions() const {
        return negativeConditions;
    }

    void setNegativeConditions(const std::vector<std::string> &negativeConditionsVal) {
        CA::negativeConditions = negativeConditionsVal;
    }

    const std::string &getRoleToAssign() const {
        return roleToAssign;
    }

    void setRoleToAssign(const std::string &roleToAssignVal) {
        CA::roleToAssign = roleToAssignVal;
    }

    void print() {
        bool i=false;
        std::cout << "<" << roleAdmin << ",";
        for (auto & value : positiveConditions) {
            std::cout << value << "&";
        }
        for (auto & value : negativeConditions) {
            if(i)
                std::cout << "&" ;
            std::cout << "-" << value;
           i = true;
        }
        std::cout << "," << roleToAssign << ">";
    }
};