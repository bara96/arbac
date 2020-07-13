//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_UTILITY_H
#define ARBAC_UTILITY_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

class Utility {
public:
    /***
     * Split a string into an array of substrings, and returns the new array
     * @param line: string to split
     * @param delimiter: Specifies the character to use for splitting the string
     * @return An Array, containing the splitted values
     */
    static vector<string> split(const string &line, char delimiter);

    /***
     * Print an array of string
     * @param vector
     */
    static void printVector(const vector<string> &vector) {
        for (auto &value : vector)
            cout << value << " ";
        cout << "\n";
    }

    /***
     * Find a role from a vector of roles
     * @param toFind: role to find
     * @param roles: vector of roles to search in
     * @return The role element if found on the given vector, else nullptr if not found
     */
    static string findRole(const string &toFind, vector<string> roles);

    /***
     * Return true if T is instance of class Base, false otherwise
     * @tparam Base: base class
     * @tparam T: object to compare
     * @return
     */
    template<typename Base, typename T>
    static inline bool instanceof(const T *) {
        return is_base_of<Base, T>::value;
    }

    /***
     * Return a vector of users with the given role
     * @param roleSet
     * @param role
     * @return
     */
    static vector<string> findUsersWithRole(const string &role, const map<string, vector<string>> &roleSet);

    /***
     * Print a set of User-Role assignments
     * @param roleSet
     */
    static void printRoleSet(const map<string, vector<string>> &roleSet);

    /***
     * Check for positive conditions for the string
     * @param condRules
     * @param roles
     * @return
     */
    static bool everyCondition(const vector<string> &condRules, const vector<string>& roles);

    /***
     * Check for negative conditions
     * @param condRules
     * @param roles
     * @return
     */
    static bool someCondition(const vector<string> &condRules, const vector<string>& roles);

    /***
     * Check if a RoleSet is empty
     * @param roleSet
     * @return true if roleSet is empty, false otherwise
     */
    static bool isRoleSetEmpty(const map<string, vector<string>> &roleSet);
};


#endif //ARBAC_UTILITY_H
