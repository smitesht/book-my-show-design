#ifndef SHOW_H
#define SHOW_H

#include <vector>
#include <string>
#include <memory>
#include "../utils/utils.h"
#include "../Movie.cpp"
#include "../seats/Seat.cpp"
#include "ShowTime.cpp"
#include "../screen/IScreenHall.h"

using namespace std;

class IShow
{
	
public:
	virtual void updateShowPrice(SeatType seatType, double price) = 0;
	virtual int getTotalReservedSeats() = 0;
	virtual vector<shared_ptr<Seat>> getAllReservedSeats() = 0;
	virtual void displayShowDetails() = 0;
	virtual vector<shared_ptr<Seat>> reserveSeats(string rowId, vector<int> seats) = 0;
	virtual int getShowId() = 0;
	virtual Movie getMovie() = 0;
	virtual ShowTime getShowTime() = 0;
	virtual shared_ptr<IScreenHall> getScreenHall() = 0;
	virtual ShowStatus getShowStatus() = 0;
	virtual ~IShow() = default;
};

#endif // SHOW_H