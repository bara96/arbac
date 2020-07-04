//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_CA_H
#define ARBAC_CA_H


#include <string>
#include <vector>

class CA {
private:
    std::string roleAdmin;
    std::vector<std::string> positiveConditions;
    std::vector<std::string> negativeConditions;
    std::string roleToAssign;

public:
    CA();

    CA(std::string roleAdmin, std::vector<std::string> positiveConditions,
       std::vector<std::string> negativeConditions, std::string roleToAssign);

    const std::string &getRoleAdmin() const {
        return roleAdmin;
    }

    void setRoleAdmin(const std::string &roleAdminVal);

    const std::vector<std::string> &getPositiveConditions() const {
        return positiveConditions;
    }

    void setPositiveConditions(const std::vector<std::string> &positiveConditionsVal);

    const std::vector<std::string> &getNegativeConditions() const {
        return negativeConditions;
    }

    void setNegativeConditions(const std::vector<std::string> &negativeConditionsVal);

    const std::string &getRoleToAssign() const {
        return roleToAssign;
    }

    void setRoleToAssign(const std::string &roleToAssignVal);

    void print();
};


#endif //ARBAC_CA_H
