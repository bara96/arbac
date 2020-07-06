//
// Created by mbaratella on 04/07/2020.
//

#include "Utility.h"

vector<string> Utility::split(const string& line, char delimiter) {
    istringstream iss(line);
    vector<string> values;
    string s;
    while (getline( iss, s, delimiter ) ) {
        values.push_back(s);
    }
    return values;
}

string Utility::findRole(const string& toFind, vector<string> roles){
    if(roles.at(0) == "TRUE")
        return "TRUE";

    auto it = std::find(roles.begin(), roles.end(), toFind);
    if (it == roles.end())
        return "";

    int index = std::distance(roles.begin(), it);
    return roles.at(index);
};

vector<string> Utility::findUsersWithRole(const string& role, const map<string, vector<string>>& roleSet) {
    vector<string> users;
    for (auto &it : roleSet) {
        if (!empty(Utility::findRole(role, it.second))) {
            users.push_back(it.first);
        }
    }
    return users;
}

void Utility::printRoleSet(const map<string, vector<string>>& roleSet) {
    for (auto & it : roleSet)
    {
        cout << it.first << ": ";
        for(const string& role : it.second)
            cout << role << " ";
        cout << "\n";
    }
}

