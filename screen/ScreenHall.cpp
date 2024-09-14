#ifndef SCREENHALL
#define SCREENHALL

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "../utils/utils.h"
#include "../seats/Seat.cpp"
#include "IScreenHall.h"
#include "../seats/SeatFactory.cpp"

using namespace std;

class ScreenHall : public IScreenHall
{
private:
	int screenId;
	map<string, vector<shared_ptr<Seat>>> hallSeatMap;
	map<SeatType, vector<string>> categoryRowMap;
	
	friend class ScreenHallBuilder;
	ScreenHall(int id):screenId(id){}

	SeatFactory seatFactory;

public:
	void createSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId)
	{
		hallSeatMap[rowId] = seatFactory.CreateSeats(seatType, rowId, startSeatId, endSeatId);
		categoryRowMap[seatType].push_back(rowId);
	}
	void updatePrice(SeatType seatType, double price)
	{
		vector<string> seatRows = categoryRowMap[seatType];

		for (string seatRow : seatRows)
		{
			for (shared_ptr<Seat> seat : hallSeatMap[seatRow])
			{
				seat->setPrice(price);
			}
		}
	}

	vector<shared_ptr<Seat>> reserveTickets(string rowId, vector<int> seats)
	{
		vector<shared_ptr<Seat>> resSeats;

		if (hallSeatMap.find(rowId) != hallSeatMap.end())
		{
			for (int seatId : seats)
			{			
				hallSeatMap[rowId][seatId-1]->setSeatReserved();
				resSeats.push_back(hallSeatMap[rowId][seatId - 1]);
			}
		}
		else
		{
			cout << "Row ID: " << rowId << " Not found" << endl;
		}
		return resSeats;
	}

	void displaySeatingArrangment()
	{
		cout << "Screen Hall Id: " << screenId << endl<<endl;
		cout << "Seat Layout "<< endl;
		for (auto kv : hallSeatMap)
		{
			auto [rowId, seats] = kv;

			cout << rowId << "--->";

			for (shared_ptr<Seat> seat : seats)
			{
				cout << seat->getRowSeatId()  << " (" << seat->getReservationStatusToString() << "),  ";
			}

			cout <<"[" << seats[0]->getSeatTypeInString() << " $" << seats[0]->getPrice()<<  "]"<< endl;
		}
		cout << "R: Reserved" << endl;
		cout << endl;
	}

	int getScreenHallId() {
		return screenId;
	}
};

#endif // !SCREENHALL