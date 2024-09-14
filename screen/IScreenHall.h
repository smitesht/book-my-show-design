#ifndef ISCREENHALL
#define ISCREENHALL

#include <memory>
#include <vector>
#include "../utils/utils.h"
#include "../seats/Seat.cpp"

class IScreenHall
{
public:
	virtual void createSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId) = 0;
	virtual void updatePrice(SeatType seatType, double price) = 0;
	virtual vector<shared_ptr<Seat>> reserveTickets(string rowId, vector<int> seats) = 0;
	virtual void displaySeatingArrangment() = 0;
	virtual int getScreenHallId() = 0;
	virtual ~IScreenHall() = default;
};

#endif // !ISCREENHALL