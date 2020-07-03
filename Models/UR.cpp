//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>
#include <iostream>

class UR {
private:
    std::string user;
    std::string role;

public:
    UR() = default;

    UR(std::string user, std::string role) : user(std::move(user)), role(std::move(role)) {}

    const std::string &getUser() const {
        return user;
    }

    void setUser(const std::string &userVal) {
        UR::user = userVal;
    }

    const std::string &getRole() const {
        return role;
    }

    void setRole(const std::string &roleVal) {
        UR::role = roleVal;
    }

    void print() {
        std::cout << "<" << user << "," << role << ">";
    }
};
