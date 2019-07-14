// --------------------------------------------------
//course: CS216-001
//Project: Project #2
//Purpose: Example code for Project 2 (help you make progress in Project 2)
//         The program asks the user to type an actor/actress name
//         if the name is valid, then display all the co-actors in each movie which the user typed actor acts
//Author: Dennis Stephens
// *With Code used from Lab10 by Yi Pike*
// --------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>
#include <map>
#include "functions.h"
#include "imdb.h"

using namespace std;

// declare global variable (constant only)
const int ARGUMENTS = 2;   // define the required command line arguments

int main(int argc, char* argv[]) {

	// Check whether the number of command line arguments match the required one 
	if (argc != ARGUMENTS) {

		cout << "Warning: need exactly one command line argument." << endl;
        	cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        
	return 1;
    	}

    	ifstream in_file;
    	in_file.open(argv[1]);
    	
	// Check whether the input file can be open successfully or not
    	if (!in_file.good()) {

        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        
	return 2;
	}
    
	// Read data from the input file, assume "good data" from the input file
    	// each line of the input file: actor name, movie1, movie2, ..., movien
    	// read one line at a time then tokenize it:
    	// create a pair <actor_name, the set of movieTitles which the actor was in>
    	//        and insert to IMDB object
    
	IMDB cs216_imdb;

    	while (!in_file.eof()) {

        	string line;
	        getline(in_file, line);
        	string name, movie;
	        istringstream iss(line);
        	getline(iss, name,',');
        
	        // Extract extra white space
       		iss>>ws;

	        // Create a new set of movies assocatiated with name
        	set<string> movies;

        while (getline(iss, movie, ',')) {

		movies.insert(toLower(movie));

            	// extract white space 
            	iss>>ws;

        }

        // insert to IMDB object: cs216_imdb
        cs216_imdb.insert_an_actor(toLower(name), movies);
    	
	}
    
	// close the input file
	in_file.close();

	char menuOption; // Creates a variable used to select from the main menu.
	
	while (true) {

		cout << "This application stores information about Actors and their Movies," << endl
			<< "please choose your option (enter Q or q to quit):" << endl
			<< "1. Actors in Movies" << endl
			<< "2. Actors and Co-actors" << endl;
		
		// Gets only the first character the user inputs
		cin >> menuOption;
		cin.ignore(256, '\n');

		// Each option either corrsesponds to an IMDB function, quits the program, or is invalid.
		if (menuOption == '1') {

			cs216_imdb.actors_in_movies();

		}
		else if (menuOption == '2') {

			 cs216_imdb.actors_and_coactors();

		}
		else if (menuOption == 'q' || menuOption == 'Q') {

			break;

		}
		else {

			cout << "Invalid Option!" << endl;

		}

	}

	// Salutation!
	cout << "Thank you for using my program, bye..." << endl;

	return 0;

}
