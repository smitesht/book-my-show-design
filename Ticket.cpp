#ifndef TICKET
#define TICKET


#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "./utils/utils.h"
#include "./seats/Seat.cpp"
#include "./show/ShowTime.cpp"

using namespace std;

class Ticket
{
private:
	int ticketId;
	int showId;
	string movieName;
	ShowTime showTime;
	int screenId;
	vector<shared_ptr<Seat>> resSeats;
	double totalBookingAmount;
	string customerFullName;
	string mobileNo;
	int theaterId;
	string theaterName;
	string theaterAddress;

	friend class BookingManager;

	Ticket(int id, int showid, string moviename, ShowTime showtime, int screenid)
		:ticketId(id), showId(showid), movieName(moviename), showTime(showtime), screenId(screenid),
		totalBookingAmount(0.0), customerFullName(""), mobileNo("")
	{}

	void setTheaterDetails(int id, string name, string address) {
		theaterId = id;
		theaterName = name;
		theaterAddress = address;
	}

	void setReservedSeats(vector<shared_ptr<Seat>> seats) {
		resSeats = seats;
	}

	double calculateTotalBookingAmount() {
		totalBookingAmount = 0.0;

		for (shared_ptr<Seat> seat : resSeats) {
			totalBookingAmount = totalBookingAmount + seat->getPrice();
		}

		return totalBookingAmount;
	}

	void setCustomerData(string fullName, string mobile) {
		customerFullName = fullName;
		mobileNo = mobile;
	}

public:
	void printTicket()
	{
		auto [showHr, showMn, showDur] = showTime.getShowTime();
		cout << "Ticket ID: " <<ticketId << endl;
		cout << "Name: " << customerFullName << ", Mobile: " << mobileNo << endl;
		cout << "Theater Name: " << theaterName << ", Address: " << theaterAddress << endl;
		cout << "Show Id:" << showId << endl;
		cout << "Screen Id:" << screenId << endl;
		cout << "Movie Name:" << movieName << endl;
		cout << "Show Time: " << showHr << ":" << showMn << " , Show Duration: " << showDur << endl;
		cout << "Seats:";
		for (shared_ptr<Seat> seat : resSeats) {
			cout << seat->getSeatId() << " ,";
		}

		cout << "Total Amount Paid:" << totalBookingAmount << endl;

		cout << endl;
	}

	void cancelTicket() 
	{
		for (shared_ptr<Seat> seat : resSeats) {
			seat->setSeatUnreserved();
		}

		//cout << "Ticket ID: " << ticketId <<" has been cancelled" << endl;
		cout << "\033[1;31m" << "Ticket ID: " << ticketId << " has been cancelled" << "\033[0m" << endl;
		cout << endl;
		// more complex cancellation logic
	}
};

#endif // !TICKET