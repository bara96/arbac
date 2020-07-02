//
// Created by mbaratella on 02/07/2020.
//

#include <utility>
#include <xstring>

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

    void setUser(const std::string &user) {
        UR::user = user;
    }

    const std::string &getRole() const {
        return role;
    }

    void setRole(const std::string &role) {
        UR::role = role;
    }
};
