#ifndef SHOWTIME
#define SHOWTIME

#include <string>
#include <tuple>

using namespace std;

class ShowTime
{
private:
	int showHour;
	int showMinute;
	int showDuration;

public:
	ShowTime() {}
	ShowTime(int hour, int min, int duration)
		:showHour(hour), showMinute(min), showDuration(duration)
	{}

	tuple<int,int, int> getShowTime() { return make_tuple(showHour, showMinute, showDuration); }
	
};

#endif // !SHOWTIME