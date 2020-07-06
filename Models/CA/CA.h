//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_CA_H
#define ARBAC_CA_H

#include <iostream>
#include <string>
#include <vector>
#include "../Rule/Rule.h"

class CA : Rule {
private:
    std::string roleAdmin;
    std::vector<std::string> positiveConditions;
    std::vector<std::string> negativeConditions;
    std::string roleToAssign;

public:
    CA();

    CA(std::string roleAdmin, std::vector<std::string> positiveConditions,
       std::vector<std::string> negativeConditions, std::string roleToAssign);

    const std::string &getRoleAdmin() const override {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal) override;

    const std::vector<std::string> &getPositiveConditions() const {
        return positiveConditions;
    }

    void setPositiveConditions(const std::vector<std::string> &positiveConditionsVal);

    const std::vector<std::string> &getNegativeConditions() const {
        return negativeConditions;
    }

    void setNegativeConditions(const std::vector<std::string> &negativeConditionsVal);

    const std::string &getRoleTarget() const override {
        return roleToAssign;
    }

    void setRoleTarget(const std::string &roleToAssignVal) override;

    void print() {
        bool i=false;
        std::cout << "<" << roleAdmin << ",";

        for (auto & value : positiveConditions) {
            if(i)
                std::cout << "&" ;
            std::cout << value;
            i = true;
        }

        if(!positiveConditions.empty() && !negativeConditions.empty())
            std::cout << "&";

        i = false;
        for (auto & value : negativeConditions) {
            if(i)
                std::cout << "&" ;
            std::cout << "-" << value;
            i = true;
        }

        std::cout << "," << roleToAssign << ">";
    }
};


#endif //ARBAC_CA_H
