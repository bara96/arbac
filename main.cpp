#include <iostream>
#include "Controls/Parser.cpp"
#include "Controls/PolicyAnalyzer.cpp"
#include <ctime>
using namespace std;

int main() {
    clock_t start = clock();
    bool showLogs = true;
    bool enableCache = true;
    bool showExecTime = false;
    string filename = "../policies/policy1.arbac";
    Policy policy;

    try {
        Parser parser = Parser(filename, showLogs);
        policy = parser.parseFile();

        PolicyAnalyzer analyzer(policy, showLogs);

        if(analyzer.analyzePolicy(enableCache))
            cout << endl << "RESULT: Reachable" << endl;
        else
            cout << endl << "RESULT: Not Reachable" << endl;

    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    clock_t stop = clock();
    if(showExecTime) {
        double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
        cout << "Time elapsed: " << elapsed << endl;
    }
    return 0;
}
