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
        Policy newPolicy = PolicyAnalyzer::backwardSlicing(policy);
        newPolicy.print();
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
