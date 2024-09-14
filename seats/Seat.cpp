#ifndef SEAT
#define SEAT

#include <string>
#include "../utils/utils.h"

using namespace std;

class Seat
{
private:
	string seatID; // row + rowSeatID e.g. A21, B12
	string rowID; // A, B,...
	int rowSeatID; // 1, 2
	SeatType seatType;
	ReservationStatus reservationStatus;
	double price;
public:
	Seat(SeatType type, string rowid, int id)
		:seatType(type), rowID(rowid), rowSeatID(id),
		price(0), reservationStatus(ReservationStatus::Empty)
	{
		seatID = rowID + to_string(rowSeatID);
	}

	string getSeatId() { return seatID; }
	string getRowId() { return rowID; }
	int getRowSeatId() { return rowSeatID; }
	SeatType getSeatType() { return seatType; }
	ReservationStatus getReservationStatus() { return reservationStatus; }
	double getPrice() { return price; }
	
	void setPrice(double price) { this->price = price; }
	void setSeatReserved() { reservationStatus = ReservationStatus::Reserved; }
	void setSeatUnreserved() { reservationStatus = ReservationStatus::Empty; }
	void setSeatSelectedForBooking() { reservationStatus = ReservationStatus::Selected; }

	string getSeatTypeInString() {
		switch (seatType)
		{
		case SeatType::Gold:
			return "Gold";
			break;
		case SeatType::Silver:
			return "Silver";
			break;
		case SeatType::Vip:
			return "Vip";
			break;
		case SeatType::Premium:
			return "Premium";
			break;
		case SeatType::Executive:
			return "Executive";
			break;
		case SeatType::Standard:
			return "Standard";
			break;
		default:
			break;
		}
	}

	string getReservationStatusToString() {
		switch (reservationStatus)
		{
		case ReservationStatus::Empty:
			return " ";
			break;
		case ReservationStatus::Selected:
			return "S";
			break;
		case ReservationStatus::Reserved:
			return "R";
			break;
		default:
			break;
		}
	}

};

#endif // !SEAT