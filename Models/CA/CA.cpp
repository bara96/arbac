//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>
#include <vector>

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

    void setRoleAdmin(const std::string &roleAdmin) {
        CA::roleAdmin = roleAdmin;
    }

    const std::vector<std::string> &getPositiveConditions() const {
        return positiveConditions;
    }

    void setPositiveConditions(const std::vector<std::string> &positiveConditions) {
        CA::positiveConditions = positiveConditions;
    }

    const std::vector<std::string> &getNegativeConditions() const {
        return negativeConditions;
    }

    void setNegativeConditions(const std::vector<std::string> &negativeConditions) {
        CA::negativeConditions = negativeConditions;
    }

    const std::string &getRoleToAssign() const {
        return roleToAssign;
    }

    void setRoleToAssign(const std::string &roleToAssign) {
        CA::roleToAssign = roleToAssign;
    }
};