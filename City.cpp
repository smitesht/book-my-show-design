#ifndef CITY
#define CITY

#include <string>
#include <vector>
#include <memory>
#include "Theater.cpp"

using namespace std;

class City
{
private:
	int cityId;
	string cityName;
	vector<shared_ptr<Theater>> theaters;

public:
	City(int id, string name) :cityId(id), cityName(name) {}

	void addTheater(shared_ptr<Theater> theater) {
		theaters.push_back(theater);
	}

	vector<shared_ptr<Theater>> getAllTheater() {
		return theaters;
	}

};

#endif // !CITY