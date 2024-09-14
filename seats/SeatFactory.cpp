#ifndef SEATFACTORY
#define SEATFACTORY

#include <string>
#include <memory>
#include <vector>
#include "../utils/utils.h"
#include "../seats/Seat.cpp"

using namespace std;

class SeatFactory
{
public:
	vector<shared_ptr<Seat>> CreateSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId)
	{
		vector<shared_ptr<Seat>> seats;

		for (startSeatId; startSeatId <= endSeatId; startSeatId++)
		{
			seats.push_back(make_shared<Seat>(seatType, rowId, startSeatId));
		}

		return seats;
	}
};


#endif // !SEATFACTORY
