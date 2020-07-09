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

        if(PolicyAnalyzer::analyzePolicy(policy))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
