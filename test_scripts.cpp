//
// Created by Carlos R. Arias on 4/4/22.
//

#include "test_scripts.h"
#include "evaluator.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::stringstream;
using std::string;
using std::ostream;
using std::istream;


void Test(bool condition, const char* message, unsigned int& passedTests);


double ValidateExpressions() {
    double grade;
    stringstream inputStream;
    stringstream outputStream;
    stringstream output;

    inputStream.str(    "2+5\n"             // 1
                        "3+2*3\n"           // 2
                        "2+5*5-1*10+8/2\n"  // 3
                        "4+a\n"             // 4
                        "2+7*3+a2*5\n"      // 5
                        "2+2+2+2+2-5*2\n"   // 6
                        "5*2+4*1\n"         // 7
                        "1+1+1-1\n"         // 8
                        "2a+3+5*2\n"        // 9
                        "20/2+5");           // 10

    outputStream.str(    "{\"expr\":\"2+5\", \"result\":7, \"error\":false}\n"
                         "{\"expr\":\"3+2*3\", \"result\":9, \"error\":false}\n"
                         "{\"expr\":\"2+5*5-1*10+8/2\", \"result\":21, \"error\":false}\n"
                         "{\"expr\":\"4+a\", \"result\":0, \"error\":true}\n"
                         "{\"expr\":\"2+7*3+a2*5\", \"result\":0, \"error\":true}\n"
                         "{\"expr\":\"2+2+2+2+2-5*2\", \"result\":0, \"error\":false}\n"
                         "{\"expr\":\"5*2+4*1\", \"result\":14, \"error\":false}\n"
                         "{\"expr\":\"1+1+1-1\", \"result\":2, \"error\":false}\n"
                         "{\"expr\":\"2a+3+5*2\", \"result\":0, \"error\":true}\n"
                         "{\"expr\":\"20/2+5\", \"result\":15, \"error\":false}\n");

    int results[] = {7, 9, 21, 0, 0, 0, 14, 2, 0, 15};
    bool errors[] = {false, false, false, true, true, false, false, false, true, false};
    string JSONLines[] = {
            "{\"expr\":\"2+5\", \"result\":7, \"error\":false}",
            "{\"expr\":\"3+2*3\", \"result\":9, \"error\":false}",
            "{\"expr\":\"2+5*5-1*10+8/2\", \"result\":21, \"error\":false}",
            "{\"expr\":\"4+a\", \"result\":0, \"error\":true}",
            "{\"expr\":\"2+7*3+a2*5\", \"result\":0, \"error\":true}",
            "{\"expr\":\"2+2+2+2+2-5*2\", \"result\":0, \"error\":false}",
            "{\"expr\":\"5*2+4*1\", \"result\":14, \"error\":false}",
            "{\"expr\":\"1+1+1-1\", \"result\":2, \"error\":false}",
            "{\"expr\":\"2a+3+5*2\", \"result\":0, \"error\":true}",
            "{\"expr\":\"20/2+5\", \"result\":15, \"error\":false}",
    };

    string expression, jsonLine;
    int result;
    int test = 0;
    bool ok;
    unsigned int passedTests = 0;
    while (getline(inputStream, expression)){
        ok = Evaluate(expression, result);
        Test(!errors[test] == ok, "Evaluate return value", passedTests);
        Test(results[test] == result, "Result value", passedTests);
        if (ok){
            jsonLine = CreateJSONLine(expression, result, false);
        }else{
            jsonLine = CreateJSONLine(expression, 0, true);
        }
        Test(jsonLine == JSONLines[test], "JSON Line Construction", passedTests);
        test++;
        output << jsonLine << endl;
    }
    grade = 3.0 * passedTests;
    passedTests = 0;
    Test(outputStream.str() == output.str(), "Full Output Matched", passedTests);
    grade += passedTests * 10;

    return grade;

}

void Test(bool condition, const char* message, unsigned int& passedTests){
    if (condition){
        cout << "TEST PASSED (" << left << setw(40) << message << ") Total Passed: " << ++passedTests << endl;
    }else{
        cout << "TEST FAILED (" << message << ")" << endl;
    }
}