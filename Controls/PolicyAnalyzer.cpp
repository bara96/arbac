//
// Created by mbaratella on 04/07/2020.
//

#include <utility>
#include <vector>
#include <map>
#include <string>
#include "../Controls/Cache.cpp"
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

        return bruteForce(reducedPolicy);
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
    * Assign an user-role pair to the roleSet map
    * @param user : user to assign
    * @param role : role to assign
    * @param roleSet : origin roleSet
    * @return
    */
    static map<string,vector<string>> assignUserRole(const string& user, const string& role, map<string, vector<string>> &roleSet, const string& roleGoal, int &found) {
        map<string,vector<string>> roleSetTemp(roleSet);
        if (!empty(roleSetTemp.find(user)->second)) {
            roleSetTemp.at(user).push_back(role);
            if(role == roleGoal)
                found = 1;
            return roleSetTemp;
        }
        else
            roleSetTemp.clear();
        map<string,vector<string>> empty;    //TODO consider to swap nullptr
        return empty;
    }

    /***
     * Revoke an user-role pair to the roleSet map
     * @param user : user to assign
     * @param role : role to assign
     * @param roleSet : origin roleSet
     * @return
     */
    static map<string,vector<string>> revokeUserRole(const string& user, const string& role, map<string, vector<string>> &roleSet) {
        map<string,vector<string>> roleSetTemp(roleSet);
        if (!empty(roleSetTemp.find(user)->second)) {
            auto it = find(roleSetTemp.at(user).begin(), roleSetTemp.at(user).end(), role);
            if (it != roleSetTemp.at(user).end()) {
                roleSetTemp.at(user).erase(it);
            }
        }
        else
            roleSetTemp.clear();
        map<string,vector<string>> empty;    //TODO consider to swap nullptr
        return empty;
    }

    /***
     * Get new tries given a roleSet and a Policy
     * @param policy
     * @param roleSet
     * @param newTries
     * @return
     */
    static int getNewTries(const Policy& policy, map<string, vector<string>>& roleSet, vector<map<string, vector<string>>>& newTries) {
        int found = 0;
        bool changes = false;

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
                            map<string, vector<string>> assigment = assignUserRole(it.first, assign.getRoleTarget(), roleSet, policy.getGoal(), found);     //do a role assignment
                            if (!empty(assigment)) {
                                newTries.push_back(assigment);
                                changes = true;
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
                    map<string, vector<string>> revocation = revokeUserRole(it.first, revoke.getRoleTarget(), roleSet);    //do a role revocation
                    if (!empty(revocation) && !Utility::isRoleSetEmpty(revocation)) {
                        newTries.push_back(revocation);
                        changes = true;
                    }
                }
            }
        }

        if(!changes)
            found = -1;

        return found;
    }

    /***
     * Try all the possible combinations
     * @param policy : the source Policy
     * @return
     */
    bool bruteForce(const Policy& policy) const{
        //build set of initial roles
        map<string, vector<string>> initialRoles = buildInitialRoles(policy);
        vector<map<string,vector<string>>> tried;   //set of all the tries
        tried.push_back(initialRoles);
        int found = 0;
        int i = 1;

        while (found == 0){
            if(isShowLogs())
                cout << "- Iteration step n'" << i << endl;
            vector<map<string, vector<string>>> newTries;      //set of the current tries
            for (map<string,vector<string>>& roleSet: tried) {
                if(found == 0)
                    found = getNewTries(policy, roleSet, newTries);
            }

            if(found > 0){
                if(isShowLogs())
                    cout << "- Target reached at iteration step n'" << i << endl;
                return true;
            }
            else {
                if(isShowLogs())
                    cout << "- Target not reached, proceding to next iteration step" << endl;
            }

            tried.insert(tried.end(), newTries.begin(), newTries.end());    //add mew tries to the tried set
            ++i;
        }

        tried.shrink_to_fit();

        return found;
    }

    /***
     * Try all the possible combinations
     * @param policy : the source Policy
     * @return
     */
    bool bruteForceCache(const Policy& policy) const{
        int found = 0;
        int i = 1;
        bool isOnBuffer = false;
        map<string, vector<string>> initialRoles = buildInitialRoles(policy);
        Cache cache = Cache();
        cache.storeSet(initialRoles);

        while (found == 0){
            if(isShowLogs())
                cout << "- Iteration step n'" << i << endl;

            vector<map<string, vector<string>>> newTries;      //set of the current tries
            ifstream inputStream;
            inputStream.open(cache.getFilename());
            while (inputStream.peek() != EOF) {
                map<string, vector<string>> roleSet = cache.readSet<string>(inputStream);
                //Check Can Assign Rules
                if(found == 0)
                    found = getNewTries(policy, roleSet, newTries);

                if(newTries.size() >= 100000) {
                    for(const auto& set : newTries) {
                        cache.storeSet(set, cache.Source::BUFFER);
                    }
                    isOnBuffer = true;
                    newTries.clear();
                }
            }

            inputStream.close();

            if(found > 0){
                if(isShowLogs())
                    cout << "- Target reached at iteration step n'" << i << endl;
                return true;
            }
            else {
                if(isShowLogs())
                    cout << "- Target not reached, proceding to next iteration step" << endl;
            }

            if(isOnBuffer) {
                cache.copyBufferOnCache();
                isOnBuffer = false;
            }
            for(const auto& set : newTries) {
                cache.storeSet(set);
            }
            newTries.clear();

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
                cout << "- approximated analysis inconclusive" << endl;
        }

        //third step: brute force
        if(isShowLogs())
            cout << "3) Evaluation" << endl;
        bool result = bruteForceCache(sourcePolicy);
        if(isShowLogs())
            cout << "ANALYZER END" << endl;
        return result;
    }
};