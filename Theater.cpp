
#ifndef THEATER
#define THEATER

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "./screen/IScreenHall.h"
#include "./show/IShow.h"
#include "./Movie.cpp"

using namespace std;


class Theater {
private:
	int theaterId;
	string theaterName;
	string theaterAddress;

	vector<shared_ptr<IScreenHall>> screenHalls;
	vector<shared_ptr<IShow>> shows;
	vector<shared_ptr<Movie>> movies;

public:

	Theater(int id, string name, string address)
		:theaterId(id), theaterName(name), theaterAddress(address)
	{}

	void addScreenHall(shared_ptr<IScreenHall> screenHall) {
		screenHalls.push_back(screenHall);
	}

	void addShow(shared_ptr<IShow> show) {
		shows.push_back(show);
	}

	void addMovie(shared_ptr<Movie> movie) {
		movies.push_back(movie);
	}

	vector<shared_ptr<IScreenHall>> getAllScreenHalls() {
		return screenHalls;
	}

	vector<shared_ptr<IShow>> getAllRunningShows() {

		vector<shared_ptr<IShow>> runningShows;

		for (shared_ptr<IShow> show : shows)
		{
			if (show->getShowStatus() == ShowStatus::Running) {
				runningShows.push_back(show);
			}
		}

		return runningShows;
	}

	shared_ptr<IShow> getShowById(int showId) {

		for (shared_ptr<IShow> show : shows) {
			if (show->getShowId() == showId) {
				return show;
			}
		}

		return nullptr;

	}

	int getTheaterId() { return theaterId; }
	string getTheaterName() { return theaterName; }
	string getTheaterAddress() { return theaterAddress; }

};

#endif // !THEATER