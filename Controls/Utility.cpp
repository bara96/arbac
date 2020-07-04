//
// Created by mbaratella on 02/07/2020.
//
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
    static vector<string> split(const string& line, char delimiter) {
        istringstream iss(line);
        vector<string> values;
        string s;
        while (getline( iss, s, delimiter ) ) {
            values.push_back(s);
        }
        return values;
    }

    /***
     * Print an array of string
     * @param vector
     */
    static void printVector(const vector<string>& vector) {
        for (auto & value : vector)
            cout << value << " ";
        cout << "\n";
    }

};
