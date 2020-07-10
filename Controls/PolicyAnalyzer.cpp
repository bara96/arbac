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
    static Policy & backwardSlicing(Policy & policy){
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
    static bool approximatedAnalysis(const Policy& policy) {
        Policy reducedPolicy = Policy(policy);
        vector<CA> reducedCa;
        for(CA ca: reducedPolicy.getCanAssign()) {
            vector<string> negativeConditions;
            ca.setNegativeConditions(negativeConditions);
            reducedCa.push_back(ca);
        }
        reducedPolicy.setCanAssign(reducedCa);

        map<string, vector<string>> initRoles = buildInitialRoles(policy);
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
    static bool bruteForce(map<string,vector<string>>& initialRoles, const Policy& policy, bool showLogs = false){
        vector<map<string,vector<string>>> tried;   //set of all the tries
        tried.push_back(initialRoles);
        bool found = false;
        int i = 1;

        while (!found){
            if(showLogs)
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
                if(showLogs)
                    cout << "- Target reached at iteration step n'" << i << endl;
            }
            else {
                if(showLogs)
                    cout << "- Target not reached, proceding to next iteration step" << endl;
            }

            tried.insert(tried.end(), newTries.begin(), newTries.end());    //add mew tries to the tried set
            ++i;
        }
        return found;
    }

public:
    static bool analyzePolicy(Policy& policy, bool showLogs = false) {
        //first step: backward slicing
        if(showLogs)
            cout << "ANALYZER BEGIN" << endl;
        if(showLogs)
            cout << "1) backward slicing" << endl;
        PolicyAnalyzer::backwardSlicing(policy);

        //second step: approximated analysis
        if(showLogs)
            cout << "2) approximated analysis" << endl;
        if(!PolicyAnalyzer::approximatedAnalysis(policy)) {
            if(showLogs) {
                cout << "- approximated analysis succeeded" << endl;
                cout << "ANALYZER END" << endl;
            }
            return false;
        }
        else {
            if(showLogs)
                cout << "- approximated analysis failed" << endl;
        }

        //third step: brute force
        if(showLogs)
            cout << "3) Evaluation" << endl;
        map<string, vector<string>> initRoles = buildInitialRoles(policy);
        bool result = bruteForce(initRoles, policy, showLogs);
        if(showLogs)
            cout << "ANALYZER END" << endl;
        return result;
    }
};