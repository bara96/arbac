//
// Created by mbaratella on 04/07/2020.
//


#include <vector> //std::vector
#include "../Models/Policy/Policy.h"

using namespace std;

class PolicyAnalizer {
private:

template <class T>
    vector<T> updatePolicy(vector<T>  v1, vector<string> & v2){
        vector<T> aux;
        for (T x : v1)
            if (Utility::findRole(x.getRoleAdmin(),v2))
                aux.push_back(x);
        return aux;
    }

    Policy & backwardSlicing(Policy & policy){
        vector<string> S;
        S.push_back(policy.getGoal());
        for (int i=0;i<100;++i){
            for (CA ca : policy.getCanAssign())
               if(empty(Utility::findRole(ca.getRoleToAssign(),S))){
                   S.push_back(ca.getRoleAdmin());
                   for (string r: ca.getNegativeConditions())
                       S.push_back(r);
                   for (string r: ca.getPositiveConditions())
                       S.push_back(r);
               }
        }
        policy.setCanAssign(updatePolicy<CA>(policy.getCanAssign(), s));
        policy.setCanRevoke(updatePolicy<CR>(policy.getCanRevoke(), s));
        return policy;
    }


};