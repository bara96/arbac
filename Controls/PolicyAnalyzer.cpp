//
// Created by mbaratella on 04/07/2020.
//


#include <utility>
#include <vector> //std::vector
#include "../Models/Policy/Policy.h"

using namespace std;

class PolicyAnalyzer {

public:
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
     * Return a reduced set of the Policy removing the negative conditions on CA
     * @param policy : the source Policy
     * @return
     */
    static Policy approximatedAnalyses(Policy policy) {
        Policy reducedPolicy = Policy(std::move(policy));
        vector<CA> reducedCa;
        for(CA ca: reducedPolicy.getCanAssign()) {
            vector<string> negativeConditions;
            ca.setNegativeConditions(negativeConditions);
            reducedCa.push_back(ca);
        }
        reducedPolicy.setCanAssign(reducedCa);
        return reducedPolicy;
    }

};