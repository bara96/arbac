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