#ifndef SHOW_PLANNER_IMPL
#define SHOW_PLANNER_IMPL

#include <memory>
#include "../utils/utils.h"
#include "ShowPlanner.cpp"

class ShowPlannerImpl : public ShowPlanner
{
public:
	ShowPlannerImpl(int id, ShowTime showTime, Movie movie, shared_ptr<IScreenHall> screenHall)
		:ShowPlanner(id,showTime,movie,screenHall)
	{}

	ShowPlanner& updateShowPrice(SeatType showType, double price)
	{
		show->updateShowPrice(showType, price);
		return *this;
	}

	shared_ptr<IShow> create() {
		return show;
	}
};

#endif