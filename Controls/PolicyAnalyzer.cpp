//
// Created by mbaratella on 04/07/2020.
//

#include <utility>
#include <vector>
#include <map>
#include <string>
#include "../Models/Policy/Policy.h"

using namespace std;

class PolicyAnalyzer {

private:
    Policy sourcePolicy;
    bool showLogs = false;

public:
    explicit PolicyAnalyzer(Policy policy, bool showLogs = false) : sourcePolicy(std::move(policy)), showLogs(showLogs) {}

    bool isShowLogs() const {
        return showLogs;
    }

    void setShowLogs(bool showLogsVal) {
        PolicyAnalyzer::showLogs = showLogsVal;
    }

    const Policy &getPolicy() const {
        return sourcePolicy;
    }

    void setPolicy(const Policy &policyVal) {
        PolicyAnalyzer::sourcePolicy = policyVal;
    }

private:
    /***
     * Filter a Rule set with a second one following the rule:
     * S[i] = S[i-1] U { Rp U Rn U roleAdmin | (roleAdmin, Rp, Rn, roleTarget) ∈ CA ∧ roleTarget ∈ S[i-1] }
     * @tparam Rule
     * @param v1
     * @param v2
     * @return
     */
    template <class Rule>
    static vector<Rule> updatePolicy(vector<Rule>  v1, vector<string> & v2){
        vector<Rule> aux;
        for (const Rule& x : v1)
            if (!empty(Utility::findRole(x.getRoleAdmin(),v2)))
                aux.push_back(x);
        return aux;
    }

    /***
     * Apply the backward slicing algorithm to reduce the policy
     * @param policy
     * @return : the policy with optimization
     */
    static Policy & backwardSlicing(Policy& policy){
        vector<string> S;
        S.push_back(policy.getGoal());
        for (int i=0;i<100;++i){
            for (const CA& ca : policy.getCanAssign())
                if(!empty(Utility::findRole(ca.getRoleTarget(), S))){
                    S.push_back(ca.getRoleAdmin());
                    for (const string& r: ca.getNegativeConditions())
                        S.push_back(r);
                    for (const string& r: ca.getPositiveConditions())
                        S.push_back(r);
                }
        }
        policy.setCanAssign(updatePolicy<CA>(policy.getCanAssign(), S));
        policy.setCanRevoke(updatePolicy<CR>(policy.getCanRevoke(), S));
        return policy;
    }

    /***
     * Create a reduced set of the Policy removing the negative conditions on CA, return true if analysis succeed, false otherwise
     * @param policy : the source Policy
     * @return : the bruteForce result on approximated analysis
     */
    bool approximatedAnalysis(const Policy& policy) {
        Policy reducedPolicy = Policy(getPolicy());
        vector<CA> reducedCa;
        for(CA ca: reducedPolicy.getCanAssign()) {
            vector<string> negativeConditions;
            ca.setNegativeConditions(negativeConditions);
            reducedCa.push_back(ca);
        }
        reducedPolicy.setCanAssign(reducedCa);

        map<string, vector<string>> initRoles = buildInitialRoles(getPolicy());
        return bruteForce(initRoles, reducedPolicy);
    }

    /***
     * Build the initial set of User-Role assignments, for each User will assign a vector of Roles
     * @param policy : the policy where to build the set
     * @return
     */
    static map<string, vector<string>> buildInitialRoles(const Policy& policy) {
        map<string, vector<string>> roleSet;
        for(const string& user: policy.getUsers()) {
            vector<string> set;
            roleSet.insert(std::pair<string,vector<string>>(user,set));
        }
        for(const UR& ur: policy.getUserRoles()) {
            auto it = roleSet.find(ur.getUser());
            it->second.push_back(ur.getRole());
        }
        return roleSet;
    }

    /***
     * Check if some user has reached the role target into the role set
     * @param roleSetAssignments
     * @param target
     * @return return true if target role is found, false otherwise
     */
    static bool targetReached(const vector<map<string,vector<string>>>& roleSetAssignments, const string& target) {
        for(const map<string,vector<string>>& roleSet: roleSetAssignments){
            if(!empty(Utility::findUsersWithRole(target, roleSet)))
                return true;
        }
        return false;
    }

    /***
     * Try all the possible combinations
     * @param policy : the source Policy
     * @return
     */
    bool bruteForce(map<string,vector<string>>& initialRoles, const Policy& policy) const{
        vector<map<string,vector<string>>> tried;   //set of all the tries
        tried.push_back(initialRoles);
        bool found = false;
        int i = 1;

        while (!found){
            if(isShowLogs())
                cout << "- Iteration step n'" << i << endl;
            vector<map<string, vector<string>>> newTries;      //set of the current tries
            for (map<string,vector<string>>& roleSet: tried) {
                //Check Can Assign Rules
                for (const CA& assign: policy.getCanAssign()) {
                    vector<string> admins = Utility::findUsersWithRole(assign.getRoleAdmin(), roleSet);
                    if (!empty(admins)) {
                        for (const auto &it: roleSet) {
                            vector<string> targetUserRoles = it.second;
                            bool positiveConditionsCheck = Utility::everyCondition(assign.getPositiveConditions(), targetUserRoles);    //check if it respect positive conditions
                            if (positiveConditionsCheck) {
                                bool negativeConditionsCheck = Utility::someCondition(assign.getNegativeConditions(), targetUserRoles);     //check if it respect negative conditions
                                if (!negativeConditionsCheck) {
                                    map<string, vector<string>> assigment = Utility::assignUserRole(it.first, assign.getRoleTarget(), roleSet);     //do a role assignment
                                    if (!empty(assigment)) {
                                        newTries.push_back(assigment);
                                    }
                                }
                            }
                        }
                    }
                }

                //Check Can Revoke Rules
                for (const CR &revoke: policy.getCanRevoke()) {
                    vector<string> admins = Utility::findUsersWithRole(revoke.getRoleAdmin(), roleSet);
                    if (!empty(admins)) {
                        for (const auto &it: roleSet) {
                            map<string, vector<string>> revocation = Utility::revokeUserRole(it.first, revoke.getRoleTarget(), roleSet);    //do a role revocation
                            if (!empty(revocation) && !Utility::isRoleSetEmpty(revocation)) {
                                newTries.push_back(revocation);
                            }
                        }
                    }
                }
            }

            if(targetReached(newTries, policy.getGoal())){
                found = true;
                if(isShowLogs())
                    cout << "- Target reached at iteration step n'" << i << endl;
            }
            else {
                if(isShowLogs())
                    cout << "- Target not reached, proceding to next iteration step" << endl;
            }

            tried.insert(tried.end(), newTries.begin(), newTries.end());    //add mew tries to the tried set
            ++i;
        }
        return found;
    }

public:
    bool analyzePolicy() {
        //first step: backward slicing
        if(isShowLogs())
            cout << "ANALYZER BEGIN" << endl;
        if(isShowLogs())
            cout << "1) backward slicing" << endl;
        PolicyAnalyzer::backwardSlicing(sourcePolicy);

        //second step: approximated analysis
        if(isShowLogs())
            cout << "2) approximated analysis" << endl;
        if(!PolicyAnalyzer::approximatedAnalysis(sourcePolicy)) {
            if(isShowLogs()) {
                cout << "- approximated analysis succeeded" << endl;
                cout << "ANALYZER END" << endl;
            }
            return false;
        }
        else {
            if(isShowLogs())
                cout << "- approximated analysis failed" << endl;
        }

        //third step: brute force
        if(isShowLogs())
            cout << "3) Evaluation" << endl;
        map<string, vector<string>> initRoles = buildInitialRoles(sourcePolicy);
        bool result = bruteForce(initRoles, sourcePolicy);
        if(isShowLogs())
            cout << "ANALYZER END" << endl;
        return result;
    }
};