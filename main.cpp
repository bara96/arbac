#include <iostream>
#include "Controls/Parser.cpp"

using namespace std;

int main() {
    string filename = "../policies/policy1.arbac";
    try {
        Parser parser = Parser(filename);
        parser.parseFile();
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
