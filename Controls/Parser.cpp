//
// Created by mbaratella on 02/07/2020.
//
#include <string>
#include <fstream>
#include <utility>
#include "../Models/Policy/Policy.h"

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

    Policy parseFile() {
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
                    policy.setCanRevoke(crList);
                }

                if(head == "CA") {
                    Parser::removeFirstLast(&values);
                    vector<CA> caList = Parser::getCanAssign(values);
                    policy.setCanAssign(caList);
                }

                if(head == "Goal") {
                    Parser::removeFirstLast(&values);
                    policy.setGoal(values.at(0));
                }
            }
        }
        return policy;
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
            string roleAdmin = ua.at(0);
            string roleToRevoke = ua.at(1);
            CR cr = CR(roleAdmin, roleToRevoke); //create the cr
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

            string roleAdmin = ua.at(0);    //set role admin
            string conditionLine = ua.at(1);    //get condition line, ex: cond1&cond2&-cond3
            string roleToAssign = ua.at(ua.size() - 1); //set role target

            vector<string> positiveConditions;
            vector<string> negativeConditions;
            vector<string> conditions = Utility::split(conditionLine, '&'); //split conditions
            for (auto & condition : conditions) {
                if(condition.at(0) == '-'){
                    condition.erase(0, 1);  //remove char '-'
                    negativeConditions.push_back(condition);
                }
                else
                    positiveConditions.push_back(condition);
            }

            CA ca = CA(roleAdmin, positiveConditions, negativeConditions, roleToAssign);    //create the ca
            caList.push_back(ca);
        }
        return caList;
    }
};
