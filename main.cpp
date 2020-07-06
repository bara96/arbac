#include <iostream>
#include "Controls/Parser.cpp"
#include "Controls/PolicyAnalyzer.cpp"
using namespace std;

void examples(Policy policy) {
    Policy policy1 = PolicyAnalyzer::backwardSlicing(policy);   //example of backwardSlicing
    Policy policy2 = PolicyAnalyzer::approximatedAnalyses(policy);  //example of approximatedAnalyses
    map<string, vector<string>> initRoles = PolicyAnalyzer::buildInitialRoles(policy); //example of buildInitialRoles
    vector<string> roles = Utility::findUsersWithRole("Doctor", initRoles); //example of findUsersWithRole
}

int main() {
    string filename = "../policies/policy1.arbac";
    Policy policy;
    try {
        Parser parser = Parser(filename);
        policy = parser.parseFile();
        examples(policy);
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
