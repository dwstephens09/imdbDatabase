#include <iostream>
#include "imdb.h"
#include "functions.h"

IMDB::IMDB() {

}

// Adds an actor to the actors database associated with the movies they were in
// and also adds the movie to the movies database and associates the actor to that movie.
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)  {

	// Adds the actor to the actors database and associates the set of movies to them
	actors_db[actorName] = movieTitles;

	// Iterates through the set of movies and associates that actor to each one 
	// in the movie database
	for ( auto i = movieTitles.begin(); i != movieTitles.end(); i++) {

		movies_db[*i].insert(actorName);

	}

}

/* NOT USED
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames) {

}
*/
 
// Checks to see if the movie input is in the movie database
bool IMDB::isExistingMovie(string movieTitle) const {

	// Iterates through the movie database looking for the input movie title
	if (movies_db.find(movieTitle) != movies_db.end())
		return 1;

	return 0;
}

// Checks to see if the actor input is in the actor database
bool IMDB::isExistingActor(string actorName) const {

	// Iterates through the actor database looking for the input actor
	if (actors_db.find(actorName) != actors_db.end())
		return 1;

	return 0;
}

// Returns a set of movies associated with an actor 
set<string> IMDB::find_movies_for_an_actor(string actorName) const {

	set<string> notFound;	// Default return if the actor is not in the database
	
	// Iterates through the actors database and returns the movies associated with that actor
	// if the actor is in the database
	for ( auto i = actors_db.begin(); i != actors_db.end(); i++ ) {

		if ( actorName == i->first ) 
			return i->second;
	}

	cout << "No movies found for that actor" << endl;
	return notFound;
}


// Returns a set of actors associated with a movie
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const {

	set<string> notFound;	// Default return if the movie is not in the database

	// Iterates through the movies database and returns the actors associated with that movie
	// if the movie is in the database
	for ( auto i = movies_db.begin(); i != movies_db.end(); i++ ) {

		if ( movieTitle == i->first )
			return i->second;
	}

	cout << "No movies found" << endl;
	return notFound;

}

// This is the first option in the main menu - Compares actors from two movies
void IMDB::actors_in_movies(){

	// Creates input variables, 2 for before parsing, 2 for after parsing
	string inputFirstMovie, inputSecondMovie, firstMovie, secondMovie;

	// Gets the first movie from the user and deletes unnecessary whitespace
	cout << "Please input the first movie title: ";
	getline(cin, inputFirstMovie);
	removeWhitespace(toLower(inputFirstMovie), firstMovie);

	// Gets the second movie from the user and deletes unnecessary whitespace
	cout << "Please input the second movie title: ";
	getline(cin, inputSecondMovie);
	removeWhitespace(toLower(inputSecondMovie), secondMovie);

	// If both movies are in the database continue with the suboptions, if not
	// the user gets an error message and the program goes to the main menu
	if (isExistingMovie(firstMovie) && isExistingMovie(secondMovie)) {

		char subMenuOption;	// Used to get the option from the user
	
		// Displays that both movies are in the database
		cout << "Both movies are in the database, please continue..." << endl;		

		// Loop continues until the user chooses q or Q
		while (true) {

			// Displays the users options
			cout << "Please input your menu option (enter Q or q to quit)" << endl
				<< "A -- to print all the actors in either of the two movies." << endl
				<< "C -- to print all the common actors in both of the movies." << endl
				<< "O -- to print all the actors who are in one movie, but not in both." << endl;
			
			// Gets the option from the user				
			cin >> subMenuOption;
			cin.ignore(256, '\n');

			// If they select A (A union B)
			if (subMenuOption == 'A' || subMenuOption == 'a') {

				set<string> displayActors; // Creates an empty set that will be used to display

				// Iterates through the movie database searching for both movies that were input
				for (auto i = movies_db.begin(); i != movies_db.end(); i++) {

					// If either of the movies are found, all actors in those movies are
					// inserted into the set that will be displays (IMPORTANT: Insert will
					// not insert duplicates of the same actor)
					if (i->first == firstMovie || i->first == secondMovie) {

						for (auto j = i->second.begin(); j != i->second.end(); j++)
							displayActors.insert(*j);
					}				
				}				

				// Iterates through the actors to display, displays and formats them
				cout << "All the actors in either of the two movies:" << endl;			
				for (auto i = displayActors.begin(); i != displayActors.end(); i++) 
					cout << capitalizeWords(*i) << endl;

			}

			// If they select C (A intersecting B)
			else if (subMenuOption == 'C' || subMenuOption == 'c') {

				// Creates empty sets for each movie to be compared and a display set
				set <string> firstMovieActors, secondMovieActors, displayActors;

				// Iterates through the movie database looking for each movie
				for (auto i = movies_db.begin(); i != movies_db.end(); i++) {

					// Assigns all the actors from the first movie to a set
					if (i->first == firstMovie) {

						for (auto j = i->second.begin(); j != i->second.end(); j++)
							firstMovieActors.insert(*j);
			
					}
					// Assigns all the actors from the second movie to a set
					else if (i->first == secondMovie) {

						for (auto j = i->second.begin(); j != i->second.end(); j++)
							secondMovieActors.insert(*j);
					}		
				}
				
				// If an actor appears in both sets that actor is added to the display set
				for (auto i = firstMovieActors.begin(); i != firstMovieActors.end(); i++) {
					for (auto j = secondMovieActors.begin(); j != secondMovieActors.end(); j++) {
					
						if ( *i == *j )
							displayActors.insert(*i);
	
					}
				}

				// Displays all of the actors in both movies
				cout << "Common actors in both movies:" << endl;
				for (auto i = displayActors.begin(); i != displayActors.end(); i++) 
					cout << capitalizeWords(*i) << endl;
			}

			// If the user selects O (A union B - A intersecting B)
			else if (subMenuOption == 'O' || subMenuOption == 'o') {

				// Creates empty sets for each movie to be compared and a display set
				set <string> firstMovieActors, secondMovieActors, displayActors;

				// Iterates through the movie database looking for each movie
				for (auto i = movies_db.begin(); i != movies_db.end(); i++) {

					// Assigns all the actors from the first movie to a set
					if (i->first == firstMovie) {

						for (auto j = i->second.begin(); j != i->second.end(); j++)
							firstMovieActors.insert(*j);
					}
					// Assigns all the actors from the second movie to a set
					else if (i->first == secondMovie) {

						for (auto j = i->second.begin(); j != i->second.end(); j++)
							secondMovieActors.insert(*j);
					}		
				}
				
				bool isUnique = true;	// Boolean to keep track of if an actor is only in one movie and not the other

				// Iterates through the actors in the first movie and compares that actor to every actor in the second movie
				for (auto i = firstMovieActors.begin(); i != firstMovieActors.end(); i++) {
					for (auto j = secondMovieActors.begin(); j != secondMovieActors.end(); j++) {
					
						// If the actor is in both movies, they are not unique to only one of the movies
						if ( *i == *j )
							isUnique = false;
	
					}
					// After comparing one actor to all the actors of the second movie, if they are still unique
					// they are added to the display set
					if (isUnique)
						displayActors.insert(*i);
					
					// resets the unique for the other iterations
					isUnique = true;
				}
				
				isUnique = true;

				// Same thing as the loop above, but compares each actor from the second movie to the first
				for (auto i = secondMovieActors.begin(); i != secondMovieActors.end(); i++) {
					for (auto j = firstMovieActors.begin(); j != firstMovieActors.end(); j++) {
					
						if ( *i == *j )
							isUnique = false;
	
					}
					if (isUnique)
						displayActors.insert(*i);
					
					isUnique = true;
				}
				
				// Formats and displays the actors
				cout << "Actors only in one of the two movies:" << endl;
				for (auto i = displayActors.begin(); i != displayActors.end(); i++)
					cout << capitalizeWords(*i) << endl;
			}

			// If q or Q is choosen breaks to the main menu
			else if (subMenuOption == 'Q' || subMenuOption == 'q') 

				break;	

			// Any other input is invalid
			else 

				cout << "Invalid Option!" << endl;
		}
	}
	// If one of neither of the movies are in the database, the proram will tell the user
	// which one cannot be found.
	else if (!isExistingMovie(firstMovie) && !isExistingMovie(secondMovie)) {

		cout << "Neither movie is in the database" << endl;

	}	
	else if (!isExistingMovie(firstMovie)) {

		cout << capitalizeWords(firstMovie) << " is not in the database." << endl;

	}
	else {

		cout << capitalizeWords(secondMovie) << " is not in the database." << endl;

	}

}

// Displays the co-actors of the actor that is input in each movie
void IMDB::actors_and_coactors(){

	string inputName, actorName; //Creates a string for input and a string for storing the parsed input

	cout << "Finding the co-actors of the actor by typing his/her name: ";

	// Gets the actors name from the user and removes any unnecessary whitespace
	getline(cin, inputName);
	removeWhitespace(toLower(inputName),actorName);

	// If the actor is in the database continue to find their coactors
	// If not the program displays an error message and sends the user to the main menu
	if (isExistingActor(actorName)) {

		// Finds all the movies an actor was in and assigns it to a set
		set<string> moviesActorIsIn = find_movies_for_an_actor(actorName);
		set<string> coactors;	// Used to display the coactors

		// Iterates through each movie the actor was in
		for (auto i = moviesActorIsIn.begin(); i != moviesActorIsIn.end(); i++) {

			// Uses the find actors function to assign them to the coactors set
			coactors = find_actors_in_a_movie(*i);
			// Erases the actor the user searched for from that set
			coactors.erase(actorName);
			
			// Displays the coactors
			cout << "The co-actors of " << capitalizeWords(actorName) << " in the movie \"" << capitalizeWords(*i) << "\" are:" << endl;
			for (auto j = coactors.begin(); j != coactors.end(); j++) {

				cout << capitalizeWords(*j) << endl;

			}
			cout << "***********************************" << endl;
		} 
	}
	// The actor is not in the database
	else
		cout << capitalizeWords(actorName) << " is not in the database." << endl;
}
