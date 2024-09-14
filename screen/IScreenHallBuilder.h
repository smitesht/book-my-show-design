#ifndef ISCREEN_HALL_BUILDER
#define ISCREEN_HALL_BUILDER

#include <string>
#include <memory>
#include "../utils/utils.h"
#include "../screen/IScreenHall.h"

using namespace std;

class IScreenHallBuilder
{
public:
	virtual IScreenHallBuilder& addRow(SeatType seatType, string rowId, int startSeatId, int endSeatId) = 0;
	virtual shared_ptr<IScreenHall> build() = 0;
	virtual ~IScreenHallBuilder() = default;
};

#endif // !ISCREEN_HALL_BUILDER