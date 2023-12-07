/* Title: Lab 2 - evalsteps.cpp
   Purpose: Implement the Evaluate and CreateJSONLine functions called by the main program to generate the JSON file
   with the evaluation of arithmetic expressions.
   Author:     Chris Kendall
   Date:       October 5, 2022
*/


#include "evaluator.h"
#include <cassert>
#include <sstream>


int GetFirstTerm(const string& tempExpression, const size_t& pos);
int GetLastTerm(const string& tempExpression, const size_t& pos);
bool isValid(const size_t& startingPlace, const size_t& numChars, const string& tempExpression);

/**
 * This function takes in an arithmetic expression, the function returns the value
 * that the expression evaluates to, that is if the expression is correctly formatted.
 * The operators the expression can have are: +, -, *, /, %
 * The expression doesn't have any spaces between its parts
 * Examples:
 *      2+3*5
 *      2*3+4/2
 * The function will evaluate *, / and % first left to right, and then + and - left to right.
 * For instance 2+3*5, would evaluate 3*5 first resulting in 2+15, and this one resulting in 17.
 * Expressions can be malformed. Example:
 *      4*2+3a
 * In this case the expression would evaluate to 8+3a and would not be able to move from there.
 * Two possible errors:
 *      Division by zero -- let your program crash in this case
 *      Overflow -- let the logic error
 * @param expression the string containing the arithmetic expression
 * @param value The value of evaluating the expression, or zero if the expression was malformed
 * @return true indicating that everything was OK, false otherwise.
 */
bool Evaluate(const string& expression, int& value){
    bool flag = true;
    value = INT32_MAX;
    string tempExpression = expression;

    int firstTerm, secondTerm;
    string tempString;
    while (tempExpression != tempString) {
        string::size_type pos = tempExpression.find_first_of('*');
        if (pos == string::npos) {
            pos = tempExpression.find_first_of('/');
            if (pos == string::npos) {
                pos = tempExpression.find_first_of('%');
                if (pos == string::npos) {
                    pos = tempExpression.find_first_of('-');
                    if (pos == string::npos) {
                        pos = tempExpression.find_first_of('+');
                        if (pos == string::npos) {
                            flag = false;
                            value = 0;
                            break;
                        } else {
                            size_t startingPlace = GetFirstTerm(tempExpression, pos);
                            size_t endingPlace = GetLastTerm(tempExpression, pos);
                            size_t numChars1 = (pos - startingPlace);
                            size_t numChars = (endingPlace - startingPlace);
                            tempString = tempExpression.substr(startingPlace, numChars);

                            if (isValid(startingPlace, (numChars1 - 1), tempExpression) && isValid((pos + 1), endingPlace, tempExpression)) {
                                firstTerm = stoi(tempExpression.substr(startingPlace, numChars1));
                                secondTerm = stoi(tempExpression.substr((pos + 1), numChars));
                                value = firstTerm + secondTerm;
                                tempString = to_string(value);
                                tempExpression.replace(startingPlace, (numChars + 1), tempString);
                            } else {
                                flag = false;
                                value = 0;
                                break;
                            }
                        }
                    } else {
                        size_t startingPlace = GetFirstTerm(tempExpression, pos);
                        size_t endingPlace = GetLastTerm(tempExpression, pos);
                        size_t numChars1 = (pos - startingPlace);
                        size_t numChars = (endingPlace - startingPlace);
                        tempString = tempExpression.substr(startingPlace, numChars);

                        if (isValid(startingPlace, (numChars1 - 1), tempExpression) && isValid((pos + 1), endingPlace, tempExpression)) {
                            firstTerm = stoi(tempExpression.substr(startingPlace, numChars1));
                            secondTerm = stoi(tempExpression.substr((pos + 1), numChars));
                            value = firstTerm - secondTerm;
                            tempString = to_string(value);
                            // making sure a negative result doesn't force two operators together
                            if (value < 0) {
                                if (startingPlace != 0){
                                    //tempExpression.erase((startingPlace), (numChars + 1));
                                    tempExpression.replace((startingPlace), (numChars + 1), tempString);
                                    tempExpression.erase(startingPlace-1, 1);
                                } else {
                                    tempExpression.replace(startingPlace, (numChars + 1), tempString);
                                }
                            } else {
                                tempExpression.replace(startingPlace, (numChars + 1), tempString);
                            }
                        } else {
                            flag = false;
                            value = 0;
                            break;
                        }
                    }
                } else {
                    size_t startingPlace = GetFirstTerm(tempExpression, pos);
                    size_t endingPlace = GetLastTerm(tempExpression, pos);
                    size_t numChars1 = (pos - startingPlace);
                    size_t numChars = (endingPlace - startingPlace);
                    tempString = tempExpression.substr(startingPlace, numChars);

                    if (isValid(startingPlace, (numChars1 - 1), tempExpression) && isValid((pos + 1), endingPlace, tempExpression)) {
                        firstTerm = stoi(tempExpression.substr(startingPlace, numChars1));
                        secondTerm = stoi(tempExpression.substr((pos + 1), numChars));
                        value = firstTerm % secondTerm;
                        tempString = to_string(value);
                        tempExpression.replace(startingPlace, (numChars + 1), tempString);
                    } else {
                        flag = false;
                        value = 0;
                        break;
                    }
                }
            } else {
                size_t startingPlace = GetFirstTerm(tempExpression, pos);
                size_t endingPlace = GetLastTerm(tempExpression, pos);
                size_t numChars1 = (pos - startingPlace);
                size_t numChars = (endingPlace - startingPlace);
                tempString = tempExpression.substr(startingPlace, numChars);

                if (isValid(startingPlace, (numChars1 - 1), tempExpression) && isValid((pos + 1), endingPlace, tempExpression)) {
                    firstTerm = stoi(tempExpression.substr(startingPlace, numChars1));
                    secondTerm = stoi(tempExpression.substr((pos + 1), numChars));
                    value = firstTerm / secondTerm;
                    tempString = to_string(value);
                    tempExpression.replace(startingPlace, (numChars + 1), tempString);
                } else {
                    flag = false;
                    value = 0;
                    break;
                }
            }
        } else {
            size_t startingPlace = GetFirstTerm(tempExpression, pos);
            size_t endingPlace = GetLastTerm(tempExpression, pos);
            size_t numChars1 = (pos - startingPlace);
            size_t numChars = (endingPlace - startingPlace);
            tempString = tempExpression.substr(startingPlace, numChars);

            if (isValid(startingPlace, (numChars1 - 1), tempExpression) && isValid((pos + 1), endingPlace, tempExpression)) {
                firstTerm = stoi(tempExpression.substr(startingPlace, numChars1));
                secondTerm = stoi(tempExpression.substr((pos + 1), numChars));
                value = firstTerm * secondTerm;
                tempString = to_string(value);
                tempExpression.replace(startingPlace, (numChars + 1), tempString);
            } else {
                flag = false;
                value = 0;
                break;
            }

        }
    }

    return flag;
}

/**
 * This function checks the values of the terms within each substring of expressions to see if they are valid (digits only).
 * @param startingPlace - the starting index of the term.
 * @param numChars - the value for number of chars in the term to be checked.
 * @param tempExpression - the substring expression to that is being evaluated.
 * @return a boolean telling whether or not the substring expression is valid.
 */
bool isValid(const size_t& startingPlace, const size_t& numChars, const string& tempExpression) {
    //size_t range = startingPlace + numChars - 1;
    for (size_t j = startingPlace; j <= numChars; j++) {
        if (!isdigit(tempExpression[j])) {
            return false;
        }
    }
    return true;
}

/**
 * This function gets the full first term in the expression which is being evaluated.
 * @param tempExpression - the substring expression that is beign evaluated.
 * @param pos - the position of the algebraic symbol that was found previously.
 * @return an int containing the index of the first index of the first term.
 */
int GetFirstTerm(const string& tempExpression, const size_t& pos) {
    int startingPlace = pos - 1;
    for (int i = startingPlace; isdigit(tempExpression[i-1]) || isalpha(tempExpression[i + 1]) && i > 0; i--) {
        startingPlace--;
    }
    return startingPlace;
}

/**
 * This function gets the full second term in the expression which is being evaluated.
 * @param tempExpression - the substring expression that is being evaluated.
 * @param pos - the position of the algebraic symbol that was found previously.
 * @return an int containing the index of the first index of the second term.
 */
int GetLastTerm(const string& tempExpression, const size_t& pos) {
    int endingPlace = pos + 1;
    for (int i = endingPlace; isdigit(tempExpression[i + 1]) || isalpha(tempExpression[i + 1]) && i > 0; i++) {
        endingPlace++;
    }
    return endingPlace;
}

/**
 *  Creates a JSON line given the expression that was been evaluated, the value that
 *  resulted from the evaluation and whether there was an error or not.
 *  Given the following function call:
 *  CreateJSONLine("2+5*3", 17, false)
 *  The resulting JSON (the string returned by the function) would be:
 *  {"expr":"2+5*3", "result":17, "error":false}
 * @param expression The arithmetic expression that was recently evaluated
 * @param result the result of executing the arithmetic expression
 * @param error indicates whether or not the expression wasn't valid, and therefore unable to be
 *              evaluated.
 * @return a JSON string containing the fields: expr, result and error, set with the values sent
 *          as parameter.
 */
string CreateJSONLine(const string& expression, int result, bool error){
    stringstream tempJson;
    tempJson << "{\"expr\":\"" << expression << "\", \"result\":" << result << ", \"error\":" << boolalpha << error << "}";
    return tempJson.str();
 }
