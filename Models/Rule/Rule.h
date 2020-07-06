//
// Created by mbaratella on 06/07/2020.
//

#ifndef ARBAC_RULE_H
#define ARBAC_RULE_H


#include <utility>
#include <string>

class Rule {
public:
    virtual ~Rule() {}

    virtual const std::string &getRoleAdmin() const  = 0;

    virtual void setRoleAdmin(const std::string &roleAdminVal) = 0;

    virtual const std::string &getRoleTarget() const = 0;

    virtual void setRoleTarget(const std::string &roleTargetVal) = 0;
};


#endif //ARBAC_RULE_H
