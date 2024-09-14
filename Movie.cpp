#ifndef MOVIE
#define MOVIE

#include <string>
#include <iostream>

using namespace std;

class Movie {
private:
	int movieId;
	string movieName;

public:
	Movie() {}
	Movie(int id, string name):movieId(id), movieName(name){}

	int getMovieId() { return movieId; }
	string getMovieName() { return movieName; }

	string toString() {
		cout << "Movie Id: " << movieId << " Movie Name: " << movieName << endl;
	}
};

#endif // !MOVIE