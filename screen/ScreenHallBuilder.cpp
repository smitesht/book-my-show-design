#ifndef SCREENBUILDER
#define SCREENBUILDER

#include <memory>
#include "IScreenHallBuilder.h"
#include "ScreenHall.cpp"

class ScreenHallBuilder : public IScreenHallBuilder
{
private:
	shared_ptr<IScreenHall> screenHall;

public:
	ScreenHallBuilder(int screenId){
		screenHall = shared_ptr<IScreenHall>(new ScreenHall(screenId));
	}

	IScreenHallBuilder& addRow(SeatType seatType, string rowId, int startSeatId, int endSeatId) {
		screenHall->createSeats(seatType, rowId, startSeatId, endSeatId);
		return *this;
	}

	shared_ptr<IScreenHall> build() {
		return screenHall;
	}
};


#endif // !SCREENBUILDER