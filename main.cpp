#include <iostream>
#include "Controls/Parser.cpp"
#include "Controls/PolicyAnalyzer.cpp"
using namespace std;

int main() {
    string filename = "../policies/policy1.arbac";
    Policy policy;
    try {
        Parser parser = Parser(filename);
        policy = parser.parseFile();
        Policy policy1 = PolicyAnalyzer::backwardSlicing(policy);
        Policy policy2 = PolicyAnalyzer::approximatedAnalyses(policy);
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
