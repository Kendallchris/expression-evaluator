// Title: Lab 1 - evalsteps.h
//
// Purpose: Declares the function "GetEvalSteps" which is implemented in "evalsteps.cpp"
// so it can be called by "main.cpp"
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson, Carlos Arias

#ifndef GETEVALSTEPS_EVALUATOR_H
#define GETEVALSTEPS_EVALUATOR_H

#include <iostream>
using namespace std;

bool Evaluate(const string& expression, int& value);
string CreateJSONLine(const string& expression, int result, bool error);

#endif //GETEVALSTEPS_EVALUATOR_H
