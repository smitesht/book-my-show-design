#ifndef SHOW_PLANNER
#define SHOW_PLANNER

#include <memory>
#include <string>
#include "../utils/utils.h"
#include "IShow.h"
#include "Show.cpp"

using namespace std;

class ShowPlanner
{
protected:
	shared_ptr<IShow> show;
public:
	ShowPlanner(int id, ShowTime showTime, Movie movie, shared_ptr<IScreenHall> screenHall)
		:show(shared_ptr<IShow>(new Show(id,showTime,movie,screenHall)))
	{
	}

	virtual ShowPlanner& updateShowPrice(SeatType showType, double price) = 0;
	virtual shared_ptr<IShow> create() = 0;
	virtual ~ShowPlanner() = default;
};

#endif //  SHOW_PLANNER