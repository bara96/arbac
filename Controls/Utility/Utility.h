//
// Created by mbaratella on 04/07/2020.
//

#ifndef ARBAC_UTILITY_H
#define ARBAC_UTILITY_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Utility {
public:
    /***
     * Split a string into an array of substrings, and returns the new array
     * @param line: string to split
     * @param delimiter: Specifies the character to use for splitting the string
     * @return An Array, containing the splitted values
     */
    static vector<string> split(const string& line, char delimiter);

    /***
     * Print an array of string
     * @param vector
     */
    static void printVector(const vector<string>& vector) {
        for (auto & value : vector)
            cout << value << " ";
        cout << "\n";
    }

    /***
     * Find a role from a vector of roles
     * @param toFind: role to find
     * @param roles: vector of roles to search in
     * @return The role element if found on the given vector, else nullptr if not found
     */
    static string findRole(const string& toFind, vector<string> roles);
};


#endif //ARBAC_UTILITY_H
