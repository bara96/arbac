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
            if (find(v2,x.getRoleAdmin()))
                aux.push_back(x);
        return aux;
    }

    Policy & backwardSlicing(Policy & policy){
        vector<string> s;
        s.push_back(policy.getGoal());
        for (int i=0;i<100;++i){
            for (CA x : policy.getCanAssign())
               if(find(s,x.getRoleToAssign())){
                   s.push_back(x.getRoleAdmin());
                   for (string role: x.getNegativeConditions())
                       s.push_back(role);
                   for (string role: x.getPositiveConditions())
                       s.push_back(role);
               }
        }
        policy.setCanAssign(updatePolicy<CA>(policy.getCanAssign(), s));
        policy.setCanRevoke(updatePolicy<CR>(policy.getCanRevoke(), s));
        return policy;
    }


};