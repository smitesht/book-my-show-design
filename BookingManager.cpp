#ifndef BOOKINGMANAGER
#define BOOKINGMANAGER


#include <memory>
#include "Ticket.cpp"
#include "./show/IShow.h"
#include "Theater.cpp"
#include "./payment/Payment.h"
#include "./payment/PaymentManager.cpp"

using namespace std;

class BookingManager
{
private:
	shared_ptr<Ticket> ticket;
	shared_ptr<IShow> show;		
public:
	BookingManager(int ticketId, shared_ptr<Theater> theater, shared_ptr<IShow> show)
	{
		ticket = shared_ptr<Ticket>(new Ticket(ticketId,show->getShowId(),
			show->getMovie().getMovieName(), show->getShowTime(), show->getScreenHall()->getScreenHallId()));
		ticket->setTheaterDetails(theater->getTheaterId(), theater->getTheaterName(), theater->getTheaterAddress());
		this->show = show;
	}

	BookingManager& reservedSeats(string rowId, vector<int> seats)
	{
		vector<shared_ptr<Seat>> resSeats = show->reserveSeats(rowId, seats);
		ticket->setReservedSeats(resSeats);		
		return *this;
	}

	BookingManager& addCustomerData(string fullname, string mobile) {
		ticket->setCustomerData(fullname, mobile);
		return *this;
	}

	shared_ptr<Ticket> PayAndBook(shared_ptr<Payment> paymentStrategy) {
		double ticketAmount = ticket->calculateTotalBookingAmount();
		PaymentManager payManager(paymentStrategy);
		payManager.makePayment(ticketAmount);
		return ticket;
	}
};

#endif // !BOOKINGMANAGER