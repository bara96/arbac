#include <iostream>
#include "Controls/Parser.cpp"
#include "Controls/PolicyAnalyzer.cpp"
using namespace std;

int main() {
    bool showLogs = true;
    string filename = "../policies/policy2.arbac";
    Policy policy;
    try {
        Parser parser = Parser(filename, showLogs);
        policy = parser.parseFile();

        if(PolicyAnalyzer::analyzePolicy(policy, showLogs))
            cout << endl << "RESULT: Reachable" << endl;
        else
            cout << endl << "RESULT: Not Reachable" << endl;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
