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
    bool showLogs;

public:
    explicit Parser(string filename, bool showLogs = false) : filename(std::move(filename)), showLogs(showLogs) {}

    const string &getFilename() const {
        return filename;
    }

    void setFilename(const string &filenameVal) {
        Parser::filename = filenameVal;
    }

    bool isShowLogs() const {
        return showLogs;
    }

    void setShowLogs(bool showLogsVal) {
        Parser::showLogs = showLogsVal;
    }

    Policy parseFile() {
        if(isShowLogs()) {
            cout << "PARSER BEGIN" << endl;
            cout << "1) Reading File: " << getFilename() << endl;
        }

        ifstream arbacFile(getFilename());
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
                    if(isShowLogs())
                        cout << "- Reading Roles Line" << endl;
                    Parser::removeFirstLast(&values);
                    policy.setRoles(values);
                }

                if(head == "Users") {
                    if(isShowLogs())
                        cout << "- Reading Users Line" << endl;
                    Parser::removeFirstLast(&values);
                    policy.setUsers(values);
                }

                if(head == "UA") {
                    if(isShowLogs())
                        cout << "- Reading UA Line" << endl;
                    Parser::removeFirstLast(&values);
                    vector<UR> urList = Parser::getUserRoles(values);
                    policy.setUserRoles(urList);
                }

                if(head == "CR") {
                    if(isShowLogs())
                        cout << "- Reading CR Line" << endl;
                    Parser::removeFirstLast(&values);
                    vector<CR> crList = Parser::getCanRevoke(values);
                    policy.setCanRevoke(crList);
                }

                if(head == "CA") {
                    if(isShowLogs())
                        cout << "- Reading CA Line" << endl;
                    Parser::removeFirstLast(&values);
                    vector<CA> caList = Parser::getCanAssign(values);
                    policy.setCanAssign(caList);
                }

                if(head == "Goal") {
                    if(isShowLogs())
                        cout << "- Reading Goal Line" << endl;
                    Parser::removeFirstLast(&values);
                    policy.setGoal(values.at(0));
                }
            }
        }
        if(isShowLogs())
            cout << "PARSER END" << endl;
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
                condition = std::string(condition);
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
