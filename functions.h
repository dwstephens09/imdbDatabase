/* 
 * File:   functions.h
 * Course: CS216-00x
 * Purpose: provide the function declarations for some useful operations on strings
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <string>
#include <algorithm>       // for transform() function

using namespace std;

// declare constant
const int LEN = 2;  // to store one character and one terminator

string toLower(const string &original); // transform each character in a string to lower case
string toUpper(const string &original); // transform each character in a string to upper case

void removeWhitespace(const string &original, string &output); //Removes whitespace from input
string capitalizeWords(const string original); // Capitalizes each new word
 
#endif	/* FUNCTIONS_H */

