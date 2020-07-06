//
// Created by mbaratella on 04/07/2020.
//


#include <vector> //std::vector
#include "../Models/Policy/Policy.h"

using namespace std;

class PolicyAnalyzer {

public:
    template <class Rule>
    static vector<Rule> updatePolicy(vector<Rule>  v1, vector<string> & v2){
        vector<Rule> aux;
        for (const Rule& x : v1)
            if (!empty(Utility::findRole(x.getRoleAdmin(),v2)))
                aux.push_back(x);
        return aux;
    }

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


};