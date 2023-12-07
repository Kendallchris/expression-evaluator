// Title: Lab 2 - main.cpp
//
// Purpose: Practice the methods offered by the C++ standard library string class by writing a C++ program
// that reads in an arithmetic expression and prints out a step by step evaluation of the expression.
//
// Class: CSC 2330 Fall 2022
// Author: Chris Kendall

#include "test_scripts.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::cerr;
using std::boolalpha;

bool Evaluate(const string& expression, int& value);
string CreateJSONLine(const string& expression, int result, bool error);

int main(int argc, char* argv[]) {
    double count = ValidateExpressions();
    cout << "Your approximate grade is = " << count << endl;

    string inputFileName;
    cout << "Enter expressions input file name: " << endl;
    cin >> inputFileName;
    string outputFileName;
    cout << "Enter expressions output file name: " << endl;
    cin >> outputFileName;

    ifstream fin(inputFileName);
    if(fin.fail()) {
        cerr << "Unable to open file " << inputFileName << endl;
        exit(1);
    }
    ofstream fout(outputFileName);
    if(fout.fail()) {
        cerr << "Unable to open file " << outputFileName << endl;
        exit(1);
    }

    string line, expression;
    int value;
    bool error;
    while (getline(fin, line)) {
        expression = line;
        error = Evaluate(expression, value);
        fout << CreateJSONLine(expression, value, error) << endl;
    }

    fin.close();
    fout.close();

    return 0;
}



