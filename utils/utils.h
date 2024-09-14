#ifndef UTILS_H
#define UTILS_H

enum class SeatType
{
	Gold,
	Silver,
	Vip,
	Premium,
	Executive,
	Standard
};

enum class ReservationStatus {
	Empty,
	Selected,
	Reserved
};

enum class ShowStatus
{
	Running,
	Cancelled,
	CommingSoon
};

#endif // !UTILS_H
