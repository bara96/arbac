//
// Created by mbaratella on 02/07/2020.
//
#include <sstream>
#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <regex>
#include "../Models/Policy.cpp"
#include "Utility.cpp"

using namespace std;

class Parser {
private:
    string filename;

public:
    explicit Parser(string filename) : filename(move(filename)) {}

    const string &getFilename() const {
        return filename;
    }

    void setFilename(const string &filenameVal) {
        Parser::filename = filenameVal;
    }

    void parseFile() {
        ifstream arbacFile(filename);
        if(!arbacFile.good())
            throw ("Can't open File");

        Policy policy = Policy();
        UR userRoles = UR();
        CA canAssign = CA();
        CR canRevoke = CR();

        for(string line; getline(arbacFile, line );){
            if(!line.empty()) {
                istringstream iss(line);
                vector<string> values = Utility::split(line, ' '); //split line into array of string values

                string head = *values.begin();
                if(head == "Roles") {
                    Parser::removeFirstLast(&values);
                    policy.setRoles(values);
                }

                if(head == "Users") {
                    Parser::removeFirstLast(&values);
                    policy.setUsers(values);
                }

                if(head == "UA") {
                    Parser::removeFirstLast(&values);
                    vector<UR> urList = Parser::getUserRoles(values);
                    policy.setUserRoles(urList);
                }

                if(head == "CR") {
                    Parser::removeFirstLast(&values);
                    vector<CR> crList = Parser::getCanRevoke(values);
                    policy.setCanRevoke(crList);    //TODO implement this
                }

                if(head == "CA") {
                    Parser::removeFirstLast(&values);
                    vector<CA> caList = Parser::getCanAssign(values);
                    policy.setCanAssign(caList);     //TODO implement this
                }

                if(head == "Goal") {
                    Parser::removeFirstLast(&values);
                    policy.setGoal(values.at(0));
                }
            }
        }
    }

private:
    /***
     * Remove first and last characters of the line
     * @param values
     */
    static void removeFirstLast(vector<string> *values) {
        (*values).erase((*values).begin());   //remove Header
        (*values).erase((*values).begin() + (*values).size() - 1);     //remove character ';'
    }

    /***
     * Return the UR array
     * @param urLines
     * @return
     */
    static vector<UR> getUserRoles(vector<string> urLines){
        vector<UR> urList;
        for (auto & urLine : urLines) {  //foreach element into values
            urLine.erase(urLine.begin());   //remove first char '<'
            urLine.erase(urLine.begin() + urLine.size() - 1);   //remove last char '>'
            vector<string> ua = Utility::split(urLine, ',');    //split the pair
            string user = ua.at(0);
            string role = ua.at(1);
            UR ur = UR(user, role); //create the ur
            urList.push_back(ur);
        }
        return urList;
    }

    /***
     * Return the CR array
     * @param crLines
     * @return
     */
    static vector<CR> getCanRevoke(vector<string> crLines){
        vector<CR> crList;
        for (auto & urLine : crLines) {  //foreach element into values
            urLine.erase(urLine.begin());   //remove first char '<'
            urLine.erase(urLine.begin() + urLine.size() - 1);   //remove last char '>'
            vector<string> ua = Utility::split(urLine, ',');    //split the pair

            CR cr = CR(); //create the cr
            crList.push_back(cr);
        }
        return crList;
    }

    /***
     * Return the CA array
     * @param caLines
     * @return
     */
    static vector<CA> getCanAssign(vector<string> caLines){
        vector<CA> caList;
        for (auto & urLine : caLines) {  //foreach element into values
            urLine.erase(urLine.begin());   //remove first char '<'
            urLine.erase(urLine.begin() + urLine.size() - 1);   //remove last char '>'
            vector<string> ua = Utility::split(urLine, ',');    //split the pair

            CA ca = CA(); //create the ca
            caList.push_back(ca);
        }
        return caList;
    }
};
