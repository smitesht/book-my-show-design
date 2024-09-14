#ifndef SHOW
#define SHOW

#include <string>
#include <memory>
#include <vector>
#include "../utils/utils.h"
#include "../screen/IScreenHall.h"
#include "../show/IShow.h"

using namespace std;

class Show : public IShow
{
private:
	int showId;
	Movie showMovie;
	ShowTime showTime;
	shared_ptr<IScreenHall> screenHall;
	vector<shared_ptr<Seat>> reservedSeats;
	ShowStatus showStatus;

	friend class ShowPlanner;

	Show(int id, ShowTime showtime, Movie movie, shared_ptr<IScreenHall> screenhall )
		:showId(id), showTime(showtime),showMovie(movie), screenHall(screenhall),
		showStatus(ShowStatus::Running)
	{}
	
	void updateShowPrice(SeatType seatType, double price)
	{
		screenHall->updatePrice(seatType, price);
	}

public:
	
	int getTotalReservedSeats() override
	{
		// code to get total reserved seats
		return reservedSeats.size();
	}
	vector<shared_ptr<Seat>> getAllReservedSeats() override
	{
		// code to get all reserved seats
		return reservedSeats;
	}

	void displayShowDetails() override
	{
		auto [showHr, showMn, showDur] = showTime.getShowTime();
		cout << "Show ID: " << showId << endl;
		cout << "Movie Name: " << showMovie.getMovieName() << endl;
		cout << "Show Time: " << showHr << ":" << showMn << ", Duration: " << showDur << endl;
		screenHall->displaySeatingArrangment();

		cout << endl;
	}

	vector<shared_ptr<Seat>> reserveSeats(string rowId, vector<int> seats) override
	{
		vector<shared_ptr<Seat>> rseats = screenHall->reserveTickets(rowId, seats);
		for (shared_ptr<Seat> seat : rseats)
		{
			reservedSeats.push_back(seat);
		}

		return rseats;
	}

	int getShowId() { return showId; }

	Movie getMovie()
	{
		return showMovie;
	}
	ShowTime getShowTime()
	{
		return showTime;
	}
	shared_ptr<IScreenHall> getScreenHall()
	{
		return screenHall;
	}

	ShowStatus getShowStatus() { return showStatus; }

	void cancelShow() 
	{
		// complex cancellation show logic
		// Reset all the book seat status
		// set showStatus = ShowStatus::Cancelled
	}

};

#endif // !SHOW