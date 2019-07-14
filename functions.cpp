/* 
 * File:   functions.cpp
 * Course: CS216-001
 * Purpose: provide the function implementation for some useful operations on strings
 */
#include <iostream> 
#include "functions.h"

/*
 Returns the string which transforms each character of the parameter into lower case
 @param original the original string:
 const call by reference (no copy is made for efficiency, safe to the argument)
 @return a new string which transforms each character of the parameter into lower case
 (algorithm header file is needed for the definition of transform function)
 */
string toLower(const string &original)
{
    string result = original;
    transform(original.begin(), original.end(), result.begin(), ::tolower);
    return result;
}

/*
 It is a recursive function.
 Returns the string which transforms each character of the parameter into upper case
 @param original the original string:
 const call by reference (no copy is made for e<fficiency, safe to the argument)
 @return a new string which transforms each character of the parameter into upper case
 */
string toUpper(const string &original)
{
    static int fcount = 0; // use a static variable to count the function calling
    fcount++;   // increase count by one while calling the function
    // Base case:
    if (original.length() == 0)
        return original;
    // Recursive case:
    string first = original.substr(0,1);
    const char* front = first.c_str();
    char upperFront[LEN];
    string result;
    upperFront[0] = toupper(front[0]);
    upperFront[1] = '\0';
    result = upperFront;
    return result + toUpper(original.substr(1, original.length()-1));
}

// Removes the whitespace from input, excluding 1 space inbetween words 
void removeWhitespace(const string &original, string &output) {

	output.clear();

	// Erases the white space in between words.
	unique_copy (original.begin(), original.end(), back_insert_iterator<string>(output),
			[](char a, char b) { return isspace(a) && isspace(b);});

	// If the begining of the string contains tabs or whitespaces, erase them.
	output.erase(output.begin(), find_if(output.begin(), output.end(), bind1st(not_equal_to<char>(), '\t')));
	output.erase(output.begin(), find_if(output.begin(), output.end(), bind1st(not_equal_to<char>(), ' ')));
}


// Capitalizes new word in a string for display purposes
string capitalizeWords(const string original) {

	// Assigns the const iterator to a string that can be manipulated.
	string capitalizedWords = original;

	int stringLength = original.length(); // Assigns the input strings length to stringLength
	
	// Always capitalizes the first characer in the string
	capitalizedWords[0] = toupper(capitalizedWords[0]);

	// Searches through each character of the string, looking for blank spaces
	for (int i = 1; i < stringLength; i++) {

		// If there is a blank space, capitalize the next letter
		if (original [i-1] == ' ')
			capitalizedWords[i] = toupper(capitalizedWords[i]);

	}
	// Returns the capitalized string
	return capitalizedWords;
}

